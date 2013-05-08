
#ifndef STATS_H
#define STATS_H

#include <vector>
#include <string>

class Stats
{
	void add_stat(const std::string &name, int &stat);

private:
	std::vector<int&> stat_refs;
	std::vector<std::string> names;
};

#endif