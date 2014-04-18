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
    // the prob of word given the context
    unordered_map<string, double> context_prob;
    // the lsa confidence value
	double lsa_conf;
    // the number of occurance in the entire corpus
    uword total_occurance;
    
	vector<matrix_entry_t> list;
} word_t;

// load the corpus into lsa_word_vector with key (word) and value(lsa_word).
unordered_map<string, word_t> lsa_word_vector_load(const char *symfn);
// preprocess the lsa word vector by entrophy
void entrophy_preprocess(unordered_map<string, word_t> lsa_word_vector);