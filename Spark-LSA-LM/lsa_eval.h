//
//  lsa_eval.h
//  Spark-LSA-LM
//
//  Created by Haoyu Huang on 4/19/14.
//  Copyright (c) 2014 Spark. All rights reserved.
//

#ifndef Spark_LSA_LM_lsa_eval_h
#define Spark_LSA_LM_lsa_eval_h

#include "lsa_common.h"
#include "lsa_dev_classify.h"

typedef struct f_score {
    double precision;
    double recall;
    double f_score;
} f_score_t;

// calculate the option accuracy
double lsa_eval_option_accuracy(std::vector<gre_ans_t> correct, std::vector<gre_ans_t> predict);

// calculate the sentence accuracy
double lsa_eval_sentence_accuracy(std::vector<gre_ans_t> correct, std::vector<gre_ans_t> predict);

// calculate the options F-score
void lsa_eval_option_f_score(std::vector<gre_ans_t> correct, std::vector<gre_ans_t> predict, f_score_t &score, char option);

// calculate the sentence F-score
void lsa_eval_sentence_f_score(std::vector<gre_ans_t> correct, std::vector<gre_ans_t> predict, f_score_t &score);

#endif