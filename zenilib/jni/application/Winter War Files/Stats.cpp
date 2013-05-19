
#include "Stats.h"
#include <fstream>
#include <sstream>

#include "Game_Model.h"

#include <time.h>

using namespace std;

void Stats::add_stat(const string &name, int *stat)
{
	names.push_back(name);
	stat_refs.push_back(stat);
}

void Stats::add_stat(const string &name, float *stat)
{
	float_names.push_back(name);
	float_stats.push_back(stat);
}


void Stats::save_to_history()
{	
	if (history_time.seconds() < 5)
		return;

	stat_history.push_back(vector<int>());
	float_stat_history.push_back(vector<float>());
	
	for (int i = 0 ; i < stat_refs.size() ; i++)
		stat_history.at(stat_history.size()-1).push_back(*stat_refs[i]);

	for (int i = 0 ; i < float_stats.size() ; i++)
		float_stat_history.at(float_stat_history.size()-1).push_back(*float_stats[i]);


	history_time.reset();
	history_time.start();
}

void Stats::save_to_file()
{
	string filename = string("Stats") + Game_Model::get().get_level_name() 
		+ Zeni::itoa(Game_Model::get().get_game_id()).std_str()
		+ name;

	ofstream fout((filename + string(" Stat History.txt")).c_str());

	for (int i = 0 ; i < names.size() ; i++)
		fout << names[i] << "\t";
	
	for (int i = 0 ; i < float_names.size() ; i++)
		fout << float_names[i] << "\t";

	fout << endl;

	for (int i = 0 ; i < stat_history.size() ; i++)
	{
		for (int j = 0 ; j < stat_history.at(i).size() ; j++)
			fout << stat_history[i][j] << "\t";
		
		for (int j = 0 ; j < float_stat_history.at(i).size() ; j++)
			fout << float_stat_history[i][j] << "\t";
		
		fout << endl;
	}
	
}