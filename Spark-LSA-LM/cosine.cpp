#include "word.h"
#include "common.h"
#include <cmath>
#include <algorithm>

double cal_norm(const word_t &w)
{
	double res = 0;
	for (int i = 0; i < w.list.size(); i++) {
		res += w.list[i].cnt * w.list[i].cnt;
	}
	return sqrt(res);
}
double cosine(const word_t &w1, const word_t &w2)
{
	long long res = 0;
	int i = 0, j = 0;
	while (i < w1.list.size() && j < w2.list.size()) {
		if (w1.list[i].doc_id < w2.list[j].doc_id)
			i++;
		else if (w1.list[i].doc_id > w2.list[j].doc_id)
			j++;
		else {
			res += w1.list[i++].cnt * w2.list[j++].cnt;
		}
	}
	double norm1 = cal_norm(w1);
	double norm2 = cal_norm(w2);
	return res / (norm1 * norm2);
}