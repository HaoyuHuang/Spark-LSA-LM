//
//  lsa_ngram.h
//  Spark-LSA-LM
//
//  Created by Haoyu Huang on 4/18/14.
//  Copyright (c) 2014 HaoyuHuang. All rights reserved.
//

#ifndef Spark_LSA_LM_lsa_ngram_h
#define Spark_LSA_LM_lsa_ngram_h

#include "lsa_common.h"

typedef struct lsa_ngram_arpa {
    double p;
    
} ngram_t;

// load arpa file into ngram
void lsa_ngram_load(const char *symbfn, vector<unordered_map<std::string, double> > &ngram);
// write ngram into arpa file
void lsa_ngram_arpa(const char *symbfn, vector<unordered_map<std::string, double> > &ngram);
//make n words into one
std::string lsa_ngram_combine(vector<std::string > &mygram);
// calculate the log10(prob) of ngram in mygram, the order is N
double lsa_ngram_prob(std::string &mygram, int N, vector<unordered_map<std::string, double> > &ngram);
#endif
