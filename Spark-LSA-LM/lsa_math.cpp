#include "lsa_math.h"
#include <cmath>
#include <algorithm>

double lsa_cal_norm(const unordered_map<uword, double> &context)
{
    double res = 0;
    for (auto it = context.begin(); it != context.end(); ++it) {
        res += it->second * it->second;
    }
	return sqrt(res);
}

double lsa_cal_norm(const word_t &word)
{
	double res = 0;
    for (auto it = word.sentence_vector.begin(); it != word.sentence_vector.end(); ++it) {
        res += it->second * it->second;
    }
	return sqrt(res);
}

// calculate the consine similarity between word vector1 and word vector2
double lsa_cosine(const word_t &w1, const word_t &w2)
{
	long long res = 0;
    auto p1 = w1.sentence_vector.begin();
    auto p2 = w2.sentence_vector.begin();
    
    while (p1 != w1.sentence_vector.end() && p2 != w2.sentence_vector.end()) {
        if (p1->first < p2->first) {
            p1++;
        } else if (p1->first > p2->first) {
            p2++;
        } else {
            res += p1->second * p2->second;
            p1++;
            p2++;
        }
    }
    double norm1 = lsa_cal_norm(w1);
	double norm2 = lsa_cal_norm(w2);
	return res / (norm1 * norm2);
}

double lsa_cosine(const word_t &w1, const unordered_map<uword, double> &context)
{
    long long res = 0;
    auto p1 = w1.sentence_vector.begin();
    auto p2 = context.begin();
    
    while (p1 != w1.sentence_vector.end() && p2 != context.end()) {
        if (p1->first < p2->first) {
            p1++;
        } else if (p1->first > p2->first) {
            p2++;
        } else {
            res += p1->second * p2->second;
            p1++;
            p2++;
        }
    }
    double norm1 = lsa_cal_norm(w1);
	double norm2 = lsa_cal_norm(context);
	return res / (norm1 * norm2);
}

double lsa_pow(double base, double pow)
{
    return std::pow(base, pow);
}

// add two word vector w into the sum.
void lsa_word_vector_add(const word_t &w1, unordered_map<uword, double> &sum)
{

}

// load the word vector into armadillo matrix
mat lsa_word_vector_load(unordered_map<string, word_t*> &lsa_word_vector, word_cnt wc, sentence_cnt sc)
{
    return NULL;
}
// perform svd operation on the word vector
void lsa_svd(mat &word_vector)
{
    mat U;
    vec s;
    mat V;
    
    svd(U,s,V,word_vector, "dc");
}

double lsa_log(double num)
{
    return log10(num);
}