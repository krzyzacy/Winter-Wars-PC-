#pragma once

#include <set>
#include <fstream>

typedef int Score_t;

void get_HS(std::multiset<Score_t> &high_scores, const char *path);

void save_HS(const std::multiset<Score_t> &hs, std::ofstream &fout);
