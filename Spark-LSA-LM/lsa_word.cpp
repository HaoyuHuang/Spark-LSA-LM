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

// load the corpus into lsa_word_vector with key (word) and value(lsa_word).
int lsa_word_vector_load(const char *symfn, unordered_map<string, word_t> &word_vector)
{
    int ret = -1;
    std::string line;
    std::ifstream fin (symfn);
    if (fin.is_open()) {
        sentence_cnt n_line = 0;
        word_cnt n_word = 0;
        while (getline (fin,line)) {
            const char  *delim = " \t";
            std::vector<std::string> words;
            split(line, words, delim);
            n_line++;
            if(words.size() == 0) {
                spark_debug("file %s, wrong line %llu\n", symfn, n_line);
                continue;
            }
            for (int i = 0; i < words.size(); i++) {
                unordered_map<string, word_t>::const_iterator value = word_vector.find(words[i]);
                word_t word_r;
                if (value == word_vector.end()) {
                    // word is not in the word vector
                    word_r.wordId = n_word;
                    word_r.total_occurance = 1;
                    n_word++;
                    word_vector.emplace(words[i], word_r);
                } else {
                    // the word is in the word vector
                    word_r = value->second;
                    word_r.total_occurance++;
                    cout << endl << value->first << " " << word_r.total_occurance << endl;
                }
                unordered_map<uword, double>::const_iterator s_vec = word_r.sentence_vector.find(n_line);
                if (s_vec == word_r.sentence_vector.end()) {
                    // the sentence is not in the sentence vector
                    word_r.sentence_vector.emplace(n_line, 1);
                } else {
                    // the sentence is in the sentence vector
                    word_r.sentence_vector.emplace(s_vec->first, s_vec->second + 1);
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
void entrophy_preprocess(unordered_map<string, word_t> &lsa_word_vector)
{

}

// calculate the context probability and confidence value
void cal_prob(unordered_map<string, word_t> &lsa_word_vector)
{

}