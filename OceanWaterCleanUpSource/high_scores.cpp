#include "high_scores.h"

#include <set>
#include <fstream>

using namespace std;

void get_HS(multiset<Score_t> &high_scores, const char *path)
{	
	ifstream fin(path);

	Score_t score;
	while (fin >> score)
		high_scores.insert(score);

	fin.close();
}

void save_score(const Score_t &score, ofstream &fout)
{
	fout << score << endl;
}

void save_HS(const multiset<Score_t> &hs, ofstream &fout)
{
	for (multiset<Score_t>::iterator i = hs.begin() ; 
			i != hs.end() ; i++)
		save_score(*i, fout);
}