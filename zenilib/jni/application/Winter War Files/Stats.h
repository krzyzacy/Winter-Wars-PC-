
#ifndef STATS_H
#define STATS_H

#include <vector>
#include <string>

#include <zenilib.h>

class Stats
{
public:
	Stats(const std::string &name_) :
	  name(name_)
	  {history_time.start();}

	  ~Stats()
	  {history_time.stop();}

	void add_stat(const std::string &name, int *stat);
	
	void add_stat(const std::string &name, float *stat);

	void save_to_history();

	void save_to_file();
	void load_from_file();

	void send_to_server();

	std::string name;
private:
	std::vector<int*> stat_refs;
	std::vector<float*> float_stats;
	std::vector<std::string> names;

	std::vector<std::vector<int>> stat_history;
	
	std::vector<std::vector<float>> float_stat_history;
	std::vector<std::string> float_names;

	Zeni::Chronometer<Zeni::Time> history_time;
};

#endif