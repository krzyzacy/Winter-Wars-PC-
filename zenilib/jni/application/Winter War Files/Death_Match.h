#ifndef DEATH_MATCH_H
#define DEATH_MATCH_H

#include "Level.h"

class Death_Match: public Level
{
public:
	Death_Match();
	virtual ~Death_Match();

	Player_View *create_player_view(Player *p) override;

protected:
	bool win() override;

private:
	

};

#endif