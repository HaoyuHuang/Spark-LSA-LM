//
//  lsa_word.cpp
//  Spark-LSA-LM
//
//  Created by Haoyu Huang on 4/18/14.
//  Copyright (c) 2014 Spark. All rights reserved.
//

#include "lsa_word.h"
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
void lsa_entropy_preprocess(unordered_map<string, word_t*> &lsa_word_vector)
{
    for (auto it = lsa_word_vector.begin(); it != lsa_word_vector.end(); ++it) {
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

// calculate the context probability and confidence value
void lsa_cal_confidence_val(unordered_map<string, word_t*> &lsa_word_vector, word_cnt wc, sentence_cnt sc)
{
    for (auto it = lsa_word_vector.begin(); it != lsa_word_vector.end(); ++it) {
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

void lsa_cal_context_prob(unordered_map<string, word_t*> &lsa_word_vector, word_cnt wc, sentence_cnt sc)
{

}