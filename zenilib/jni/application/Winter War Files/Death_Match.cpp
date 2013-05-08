#include "Death_Match.h"
#include "Team.h"
#include "Globals.h"

Death_Match::Death_Match()
{
	//Stop player from being able to build structures
	parameters.find("Max Resources").set_value(0.0f);

}

Death_Match::~Death_Match() 
{
	parameters.find("Max Resources").reset();
}

bool Death_Match::win()
{
	Team* winning_team = nullptr;
	bool tie = false;

	for(int i = 0; i < 4; i++)
	{
		Team* t = get_team(i);
		if(!winning_team)
		{
			winning_team = t;
		}
		else if(t->get_Player_Kills() == winning_team->get_Player_Kills())
		{
			tie = true;
		}
		else if(t->get_Player_Kills() > winning_team->get_Player_Kills())
		{
			winning_team = t;
			tie = false;
		}
	}

	if(!tie) 
		set_winning_team(winning_team);
	else set_winning_team(nullptr);

	if(get_time_passed() >= parameters.find("Timer Deathmatch").get_value())
	{
		return true;
	}
	else if(!tie && 
		    winning_team->get_Player_Kills() >= parameters.find("Max Kills Deathmatch").get_value())
	{
		return true;
	}

	return false;
}
