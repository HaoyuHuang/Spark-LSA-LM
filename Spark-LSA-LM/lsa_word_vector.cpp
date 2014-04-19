//
//  lsa_word.cpp
//  Spark-LSA-LM
//
//  Created by Haoyu Huang on 4/18/14.
//  Copyright (c) 2014 Spark. All rights reserved.
//

#include "lsa_word_vector.h"
#include "fst_common.h"
#include "utils.h"
#include "lsa_common.h"
#include "lsa_math.h"

// load the corpus into lsa_word_vector with key (word) and value(lsa_word).
int lsa_word_vector_load(const char *symfn, unordered_map<string, word_t *> &word_vector, word_cnt &word_cnt, sentence_cnt &sentence_cnt)
{
    int ret = -1;
    std::string line;
    std::ifstream fin (symfn);
    if (fin.is_open()) {
        word_cnt = 0;
        sentence_cnt = 0;
        while (getline (fin,line)) {
            const char  *delim = " \t";
            std::vector<std::string> words;
            split(line, words, delim);
            sentence_cnt++;
            if(words.size() == 0) {
                spark_debug("file %s, wrong line %llu\n", symfn, sentence_cnt);
                continue;
            }
            for (int i = 0; i < words.size(); i++) {
                unordered_map<string, word_t *>::const_iterator value = word_vector.find(words[i]);
                word_t *word_r;
                if (value == word_vector.end()) {
                    // word is not in the word vector
                    word_r = new word_t;
                    word_r->wordId = word_cnt;
                    word_r->total_occurance = 1;
                    word_cnt++;
                    word_vector.emplace(words[i], word_r);
                } else {
                    // the word is in the word vector
                    word_r = value->second;
                    word_r->total_occurance++;
                }
                unordered_map<uword, double>::const_iterator s_vec = word_r->sentence_vector.find(sentence_cnt);
                if (s_vec == word_r->sentence_vector.end()) {
                    // the sentence is not in the sentence vector
                    word_r->sentence_vector.emplace(sentence_cnt, 1);
                } else {
                    // the sentence is in the sentence vector
                    word_r->sentence_vector.emplace(s_vec->first, s_vec->second + 1);
                }
            }
        }
        fin.close();
    } else {
        spark_debug("open file %s failed", symfn);
        return ret;
    }
    return 0;
}

// preprocess the lsa word vector by entrophy
void lsa_entropy_preprocess(unordered_map<string, word_t*> &word_vector)
{
    for (auto it = word_vector.begin(); it != word_vector.end(); ++it) {
        word_t *word_r = it->second;
        unordered_map<uword, double> sentence_vector = word_r->sentence_vector;
        double sum = 0;
        for (auto em = sentence_vector.begin(); em != sentence_vector.end(); ++em) {
            double log = lsa_log(em->second+1);
            sum += -log * (em->second + 1);
            em->second = log;
        }
        
        for (auto em = sentence_vector.begin(); em != sentence_vector.end(); ++em) {
            em->second /= sum;
        }
    }
}

// calculate the confidence value
void lsa_cal_confidence_val(unordered_map<string, word_t*> &word_vector, word_cnt wc, sentence_cnt sc)
{
    for (auto it = word_vector.begin(); it != word_vector.end(); ++it) {
        word_t *word_r = it->second;
        unordered_map<uword, double> sentence_vector = word_r->sentence_vector;
        double sum = 0;
        for (auto em = sentence_vector.begin(); em != sentence_vector.end(); ++em) {
            double pji = em->second / word_r->total_occurance;
            sum += pji * lsa_log(pji);
        }
        word_r->lsa_conf = 1 + sum / lsa_log(sc);
    }
}

// calculate the context probability and the score for the sentence.
double  lsa_cal_total_similarity_with_ngram(unordered_map<string, word_t*> &word_vector, word_cnt wc, sentence_cnt sc, vector<string> context, vector<int> blank, double r)
{
    double res = 0;
    int i = 0;
    // add up all context vectors
    unordered_map<uword, double> context_vec;
    for (i = 0; i < context.size(); i++) {
        if (blank[i] == LSA_SENTENCE_CONTEXT) {
            unordered_map<string, word_t*>::const_iterator value = word_vector.find(context[i]);
            if (value != word_vector.end()) {
                lsa_word_vector_add(*value->second, context_vec);
            }
        }
    }
    // calculate each word vector cosine similarity with context.
    double min = 0;
    long double sum = 0;
    std::vector<double> word_cosine_prob;
    for (auto it = word_vector.begin(); it != word_vector.end(); ++it) {
        double value = lsa_cosine(*it->second, context_vec);
        sum += value;
        word_cosine_prob.push_back(value);
        if (value < min) {
            min = value;
        }
    }
    // calculate each word vector cosine similarity with pow r.
    long double sum_r = 0;
    for (i = 0; i < word_cosine_prob.size(); i++) {
        word_cosine_prob[i] = (word_cosine_prob[i] - min) / sum;
        word_cosine_prob[i] = lsa_pow(word_cosine_prob[i], r);
        sum_r += word_cosine_prob[i];
    }
    
    i = 0;
    double temp = 0;
    while (i < context.size()) {
        if (blank[i] == LSA_SENTENCE_CONTEXT) {
            i++;
        } else {
            unordered_map<string, word_t*>::const_iterator value = word_vector.find(context[i]);
            if (value != word_vector.end()) {
                // the LSA probability for the word in the blank
                temp += word_cosine_prob[value->second->wordId] / sum_r;
                
            }
        }
    }
    return res;
}

// calculate the total cosine similarity for the options in the context. Each option is calculated independently and the individual cosine similarity with the context is then sumed up.
double lsa_cal_total_similarity(unordered_map<string, word_t*> &word_vector, word_cnt wc, sentence_cnt sc, vector<string> context, vector<string> options)
{
    double res = 0;
    int i = 0;
    // add up all context vectors
    unordered_map<uword, double> context_vec;
    for (i = 0; i < context.size(); i++) {
        unordered_map<string, word_t*>::const_iterator value = word_vector.find(context[i]);
        if (value != word_vector.end()) {
            lsa_word_vector_add(*value->second, context_vec);
        }
    }
    for (i = 0; i < options.size(); i++) {
        unordered_map<string, word_t*>::const_iterator value = word_vector.find(options[i]);
        if (value != word_vector.end()) {
            res += lsa_cosine(*value->second, context_vec);
        }
    }
    return res;
}