#ifndef lsa_word_vector
#define lsa_word_vector
#define LSA_SENTENCE_CONTEXT 0

#include "lsa_common.h"
#include <unordered_map>

typedef struct lsa_entry {
	int cnt;
    uword doc_id;
} matrix_entry_t;

typedef struct lsa_word {
    // the wordId. (every distinct word has a unique word id)
    uword wordId;
    // the sentence vector. key is the sentence id and value is the number of occurence of the word in the sentence.
    unordered_map<uword, double> sentence_vector;
    // the lsa confidence value
	double lsa_conf;
    // the number of occurance in the entire corpus
    uword total_occurance;
} word_t;

// load the corpus into lsa_word_vector with key (word) and value(lsa_word).
int lsa_word_vector_load(const char *symfn, unordered_map<string, word_t*> &word_vector, word_cnt &word_cnt, sentence_cnt &sentence_cnt);

// preprocess the lsa word vector by entrophy
void lsa_entropy_preprocess(unordered_map<string, word_t*> &word_vector);

// calculate the confidence value
void lsa_cal_confidence_val(unordered_map<string, word_t*> &word_vector, word_cnt wc, sentence_cnt sc);

// calculate the context probability and the score for the sentence.
double lsa_cal_total_similarity_with_ngram(unordered_map<string, word_t*> &word_vector, word_cnt wc, sentence_cnt sc, vector<string> context, vector<int> blank, double r);

// calculate the total cosine similarity for the options in the context. Each option is calculated independently and the individual cosine similarity with the context is then sumed up.
double lsa_cal_total_similarity(unordered_map<string, word_t*> &word_vector, word_cnt wc, sentence_cnt sc, vector<string> context, vector<string> options);

#endif