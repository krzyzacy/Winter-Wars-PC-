#include "Level.h"
#include "Tutorial_Level.h"
#include "Claim_Tree_Level.h"
#include "Death_Match.h"
#include "Kill_Snowmen.h"

#include <vector>

using namespace std;

vector<string> get_levels_names()
{
	vector<string> list;
	list.push_back("Tutorial");
	list.push_back("Claim Tree");
	list.push_back("Death Match");
	list.push_back("Kill the Snowman");

	return list;
}

Level *create_level(const string &type)
{
	if (type == "Tutorial")
		return new Tutorial_Level();
	
	if (type == "Claim Tree")
		return new Claim_Tree_Level();
		//return new Death_Match();

	if (type == "Kill the Snowmen")
		return new Kill_Snowmen;

	if (type == "Death Match")
		return new Death_Match();

	throw type;
}