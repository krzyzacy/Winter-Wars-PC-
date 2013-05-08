
#include "Stats.h"

using namespace std;

void Stats::add_stat(const string &name, int &stat)
{
	names.push_back(name);
	stat_refs.push_back(stat);
}
