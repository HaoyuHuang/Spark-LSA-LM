//
//  lsa_classify.h
//  Spark-LSA-LM
//
//  Created by Haoyu Huang on 4/19/14.
//  Copyright (c) 2014 Spark. All rights reserved.
//

#ifndef Spark_LSA_LM_lsa_dev_classify_h
#define Spark_LSA_LM_lsa_dev_classify_h

#include "lsa_word_vector.h"

#define OPTION_A 'A'
#define OPTION_B 'B'
#define OPTION_C 'C'
#define OPTION_D 'D'
#define OPTION_E 'E'

typedef struct answer {
    // each sentence completion task may contain several blanks need to be filled.
    std::vector<char> answers;
} gre_ans_t;

// option is a struct to represent each option in the sentence completion task
typedef struct option {
    // the option_id indicates each option ()
    char option_id;
    // each option may contain several words need to fill in the sentence
    std::vector<string> word;
} gre_op_t;

typedef struct gre_sentence_completion_task {
    std::string sentence;
    std::vector<std::vector<option>> options;
    gre_ans_t answer;
} gre_sc_t;

// load the development set
void lsa_dev_load(char *symfn, std::vector<gre_sc_t> &tasks);

// classify the development set using LSA language model
void lsa_lm_dev_classify(std::vector<gre_sc_t> &tasks, std::vector<gre_ans_t> &result);

// classify the development set using LSA
void lsa_dev_classify(std::vector<gre_sc_t> &tasks, std::vector<gre_ans_t> &result);

#endif
