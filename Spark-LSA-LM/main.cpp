//
//  main.cpp
//  Spark-LSA-LM
//
//  Created by Haoyu Huang on 4/16/14.
//  Copyright (c) 2014 HaoyuHuang. All rights reserved.
//

#include <iostream>

#include "armadillo"
#include "lsa_word.h"

using namespace arma;
using namespace std;

int main ()
{
    unordered_map<string, word_t*> word_vector;
    word_cnt wc = 0;
    sentence_cnt sc = 0;
    lsa_word_vector_load("/Users/apple/graduate/Courses/544NLP/Workspace/Spark-LSA-LM/Spark-LSA-LM/text.txt", word_vector, wc, sc);
    cout << wc << " " << sc << endl;
    lsa_cal_confidence_val(word_vector, wc, sc);
    lsa_entropy_preprocess(word_vector);
    unordered_map<uword, double> sentence_vector = word_vector.find("ern")->second->sentence_vector;
    for (auto it = sentence_vector.begin(); it != sentence_vector.end(); ++it) {
        cout << it->first << " " << it->second << endl;
    }
    cout << word_vector.find("ern")->second->total_occurance << endl;
    cout << word_vector.find("ern")->second->lsa_conf << endl;
    return 0;
}

