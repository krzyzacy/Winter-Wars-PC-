#pragma once


#include <zenilib.h>

class Player;

class Multiplier
{
public:
	Multiplier(Player *p);
	Multiplier(const Multiplier &m, const Zeni::Point2f &) ;
		~Multiplier(void);


private:
	int in_a_row;
	Player *player;

	int give_points();
	

	void pass()
	{++in_a_row;}

	Multiplier(const Multiplier &m);

	
};

