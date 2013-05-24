#ifndef KILL_SNOWMEN_H
#define KILL_SNOWMEN_H

#include "Death_Match.h"

#include <string>

class Objective;

class Kill_Snowmen: public Death_Match
{
public:
	Kill_Snowmen();
	virtual ~Kill_Snowmen();
	
	void start_up(const std::vector<Player_info*> &player_info) override;
	void clean() override;

	std::string get_level_name() override;
	
protected:
	bool win() override;

private:
	Objective *ob;
};

#endif