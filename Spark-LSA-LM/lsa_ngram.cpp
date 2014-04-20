#include "lsa_word_vector.h"
#include "fst_common.h"
#include "utils.h"
#include "lsa_common.h"
#include "lsa_math.h"
using namespace std;
int lsa_ngram_load(const char *symbfn, vector<unordered_map<std::string, double> > &ngram)
{
    std::string line;
    std::ifstream fin (symbfn);
    int max_order = 0;
    ngram.clear();
    if (fin.is_open()) {
        while (getline(fin, line)){
            if (line == "\\Data\\") {
                break;
            }
        }
        while (getline(fin, line) && line.length() > 0) {
            max_order++;
            /*
            std::istringstream in(line);
            std::string str;
            
            in >> str;
            in >> str;
            int i = 0;
            while (i < str.length() && str[i] != '=')
                i++;
            i++;
            
            */
        }
        for (int i = 1; i  <= max_order; i++) {
            getline(fin, line); // \i-grams:
            unordered_map<std::string, double> mp;
            while (getline(fin, line) && line.length() > 0) {
                std::istringstream in(line);
                std::string str;
                std::string input_ngram = "";
                bool has_backoff = false;
                double prob, backoff;
                in >> prob;
                for (int j = 0; j < i; j++) {
                    in >> str;
                    if (j > 0) {
                        input_ngram += "@@";
                    }
                    input_ngram += str;
                }
                mp.emplace(input_ngram, prob);
                if (in >> backoff)
                    has_backoff = true;
            }
            ngram.push_back(mp);
        }
        getline(fin, line); // end
    }
    else {
        spark_debug("open file %s failed\n", symbfn);
        return -1;
    }
    return 0;
}
std::string lsa_ngram_combine(vector<std::string > &mygram) {
    std::string res = "";
    for (int i = 0; i < mygram.size(); i++) {
        if (i > 0)
            res += "@@";
        res += mygram[i];
    }
    return res;
}
double lsa_ngram_prob(std::string &mygram, int N, vector<unordered_map<std::string, double> > &ngram)
{
    std::unordered_map<std::string,double>::const_iterator got = ngram[N - 1].find (mygram);
    return got->second;
}