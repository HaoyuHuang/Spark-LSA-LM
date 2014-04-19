#ifndef lsa_math
#define lsa_math

#include "lsa_word_vector.h"

double lsa_cal_norm(const word_t &w);
double lsa_cal_norm(const unordered_map<uword, double> &context);

// calculate the consine similarity between word vector1 and word vector2
double lsa_cosine(const word_t &w1, const word_t &w2);
double lsa_cosine(const word_t &w1, const unordered_map<uword, double> &context);

double lsa_pow(double base, double pow);

// add two word vector w into the sum.
void lsa_word_vector_add(const word_t &w1, unordered_map<uword, double> &sum);

// load the word vector into armadillo matrix
mat lsa_word_vector_load(unordered_map<string, word_t*> &word_vector, word_cnt wc, sentence_cnt sc);

// perform svd operation on the word vector
void lsa_svd(mat &word_vector);

double lsa_log(double num);

#endif