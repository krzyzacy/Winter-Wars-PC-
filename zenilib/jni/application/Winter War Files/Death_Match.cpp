#include "Death_Match.h"
#include "Team.h"
#include "Globals.h"
#include "Player_Deathmatch_View.h"
#include "Player_View.h"
#include <string>

using namespace std;

Death_Match::Death_Match()
{
	//Stop player from being able to build structures
	parameters.find("Max Resources").set_value(0.0f);

}

Death_Match::~Death_Match() 
{
	parameters.find("Max Resources").reset();
}

string Death_Match::get_level_name() 
{
	return "Snowball_Fight"; 
}

bool Death_Match::win()
{
	Team* winning_team = nullptr;
	int winning_team_score = 0;
	bool tie = false;

	for(int i = 0; i < 4; i++)
	{
		Team* t = get_team(i);
		int team_score = t->get_Player_Kills() - t->get_Player_Teamkills();
		if(!winning_team)
		{
			winning_team = t;
			winning_team_score = team_score;
		}
		else if(team_score == winning_team_score)
		{
			tie = true;
		}
		else if(team_score > winning_team_score)
		{
			winning_team = t;
			winning_team_score = team_score;
			tie = false;
		}
	}

	if(!tie) 
		set_winning_team(winning_team);
	else set_winning_team(nullptr);

	if(get_time_passed() >= parameters.find("Timer Snowball Fight").get_value())
	{
		return true;
	}
	else if(!tie && 
		    winning_team_score >= parameters.find("Max Kills Snowball Fight").get_value())
	{
		return true;
	}

	return false;
}

Player_View *Death_Match::create_player_view(Player *p)
{
	return new Player_Deathmatch_View(p);
}

float Death_Match::get_time_left()
{
	return parameters.find("Timer Snowball Fight").get_value() - get_time_passed();
}
