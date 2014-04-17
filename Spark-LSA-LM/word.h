#include <vector>
#include "common.h"
#include <cstring>

typedef struct entry
{
	int cnt, doc_id;
}matrix_entry_t;
typedef struct word
{
	vector<matrix_entry_t> list;
	string word;
	double lsa_conf;
	/* prob of word given document c, p(w|c)*/
	vector<double> p_wc;
	/* likelihood of document j given that term i occurs in j
	 * count of term i in document j / count of term i in whole corpus
	 * */
	vector<double> p_ji;
}word_t;
