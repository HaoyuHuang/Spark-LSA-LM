//
//  lsa_eval.cpp
//  Spark-LSA-LM
//
//  Created by Haoyu Huang on 4/19/14.
//  Copyright (c) 2014 Spark. All rights reserved.
//

#include "lsa_eval.h"

// calculate the option accuracy
double lsa_eval_option_accuracy(std::vector<gre_ans_t> correct, std::vector<gre_ans_t> predict)
{
    double correct_ans = 0;
    double total_ans = 0;
    int i = 0;
    int j = 0;
    for (i = 0; i < correct.size(); i++) {
        std::vector<char> corr_ans = correct[i].answers;
        std::vector<char> pre_ans = predict[i].answers;
        for (j = 0; j < corr_ans.size(); j++) {
            if (corr_ans[j] == pre_ans[j]) {
                correct_ans++;
            }
            total_ans++;
        }
    }
    return correct_ans / total_ans;
}

// calculate the sentence accuracy
double lsa_eval_sentence_accuracy(std::vector<gre_ans_t> correct, std::vector<gre_ans_t> predict)
{
    double correct_ans = 0;
    double total_ans = 0;
    int i = 0;
    int j = 0;
    bool t = true;
    for (i = 0; i < correct.size(); i++) {
        std::vector<char> corr_ans = correct[i].answers;
        std::vector<char> pre_ans = predict[i].answers;
        for (j = 0; j < corr_ans.size(); j++) {
            if (corr_ans[j] != pre_ans[j]) {
                t = false;
            }
        }
        if (t) {
            correct_ans++;
        }
        t = true;
        total_ans++;
    }
    return correct_ans / total_ans;
}

// calculate the options F-score
void lsa_eval_option_f_score(std::vector<gre_ans_t> correct, std::vector<gre_ans_t> predict, f_score_t &score, char option)
{
    double precision = 0;
    double recall = 0;
    
    double kh = 0;
    double ks = 0;
    double kht = 0;
    double kst = 0;
    
    int i = 0;
    int j = 0;
    for (i = 0; i < correct.size(); i++) {
        std::vector<char> corr_ans = correct[i].answers;
        std::vector<char> pre_ans = predict[i].answers;
        for (j = 0; j < corr_ans.size(); j++) {
            if (corr_ans[j] == option) {
                kht++;
                if (pre_ans[j] == option) {
                    kh++;
                }
            }
            if (pre_ans[j] == option) {
                kst++;
                if (corr_ans[j] == option) {
                    ks++;
                }
            }
        }
    }
    precision = ks / kst;
    recall = kh / kht;
    score.precision = precision;
    score.recall = recall;
    score.f_score = (2 * precision * recall) / (precision + recall);
}

// calculate the sentence F-score
void lsa_eval_sentence_f_score(std::vector<gre_ans_t> correct, std::vector<gre_ans_t> predict, f_score_t &score)
{

}