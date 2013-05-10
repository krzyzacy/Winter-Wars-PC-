#ifndef DEATH_MATCH_H
#define DEATH_MATCH_H

#include "Level.h"

class Death_Match: public Level
{
public:
	Death_Match();
	virtual ~Death_Match();

	std::string get_level_name() override;

	Player_View *create_player_view(Player *p) override;

	float get_time_left() override;

protected:
	bool win() override;

private:
};

#endif