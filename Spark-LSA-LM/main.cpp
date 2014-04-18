//
//  main.cpp
//  Spark-LSA-LM
//
//  Created by Haoyu Huang on 4/16/14.
//  Copyright (c) 2014 HaoyuHuang. All rights reserved.
//

#include <iostream>

#include "armadillo"

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

int main(int argc, const char * argv[])
{
    // insert code here...
    std::cout << "Hello, World!\n";
    
    return 0;
}

