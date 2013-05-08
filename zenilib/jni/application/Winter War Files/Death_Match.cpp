#include "Death_Match.h"
#include "Team.h"
#include "Globals.h"

Death_Match::Death_Match()
{
	//Stop player from being able to build structures
	parameters.find("Max Resources").set_value(2050.0f);
}

Death_Match::~Death_Match() 
{
	parameters.find("Max Resources").reset();
}

bool Death_Match::win()
{
	for(int i = 0; i < 4; i++)
	{
		Team* team = get_team(i);
		if(team->get_Player_Kills() >= parameters.find("Max Kills Deathmatch").get_value())
		{
			stop();
			set_winning_team(team);
			return true;
		}
	}
	return false;
}
