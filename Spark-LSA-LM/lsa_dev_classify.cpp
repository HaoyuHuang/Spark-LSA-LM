//
//  lsa_dev_classify.cpp
//  Spark-LSA-LM
//
//  Created by Haoyu Huang on 4/19/14.
//  Copyright (c) 2014 Spark. All rights reserved.
//

#include "lsa_dev_classify.h"
#include "lsa_common.h"
#include "fst_common.h"

// load the development set
int lsa_dev_load(char *symfn, std::vector<gre_sc_t> &tasks)
{
    int ret = -1;
    std::string line;
    std::ifstream fin (symfn);
    if (fin.is_open()) {
        
    } else {
        spark_debug("open file %s failed", symfn);
        return ret;
    }
    return 0;
}

// classify the development set using LSA language model
void lsa_lm_dev_classify(std::vector<gre_sc_t> &tasks, std::vector<gre_ans_t> &result)
{

}

// classify the development set using LSA
void lsa_dev_classify(std::vector<gre_sc_t> &tasks, std::vector<gre_ans_t> &result)
{

}