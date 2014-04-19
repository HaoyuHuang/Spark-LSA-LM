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

void svd_example()
{
    mat X = randu<mat>(5,3);
    
    mat U;
    vec s;
    mat V;
    
    svd(U,s,V,X, "dc");
    X.print("original matrix:");
    U.print("k-word matrix:");
    s.print("k*k diagonal matrix:");
    V.print("k-document matrix:");
}

int main ()
{
    unordered_map<string, word_t*> word_vector;
    lsa_word_vector_load("/Users/apple/graduate/Courses/544NLP/Workspace/Spark-LSA-LM/Spark-LSA-LM/text.txt", word_vector);
    cout << word_vector.find("ern")->second->total_occurance;
    return 0;
}

