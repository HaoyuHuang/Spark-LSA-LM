#ifndef lsa_math
#define lsa_math

#include "lsa_word.h"

double cal_norm(const word_t &w);
double cosine(const word_t &w1, const word_t &w2);

// load the word vector into armadillo matrix
mat lsa_word_vector_load(unordered_map<string, word_t*> &lsa_word_vector, word_cnt wc, sentence_cnt sc);
// perform svd operation on the word vector
void lsa_svd(mat &word_vector);

double lsa_log(double num);

#endif