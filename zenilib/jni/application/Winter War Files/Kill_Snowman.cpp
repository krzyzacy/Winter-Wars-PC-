#include "Kill_Snowmen.h"
#include "Globals.h"
#include <string>

#include "Event.h"
#include "Objective.h"

using namespace std;


Kill_Snowmen::Kill_Snowmen()
{
	parameters.find("Respawn Time").set_value(2);
}

Kill_Snowmen::~Kill_Snowmen() 
{
	parameters.find("Respawn Time").reset();
}

void Kill_Snowmen::start_up(const std::vector<Player_info*> &player_info)
{
	Level::start_up(player_info);

	// Build Red team stuff
	Build_Event ev;
/*	
	ev.put_in_game(10,12,2,SNOWMAN);
	ev.put_in_game(10,11,2,SNOWMAN);
	ev.put_in_game(10,10,2,SNOWMAN);
	ev.put_in_game(10,9,2,SNOWMAN);
	ev.put_in_game(10,8,2,SNOWMAN);
	ev.put_in_game(9,11,2,SNOWMAN);
	ev.put_in_game(9,10,2,SNOWMAN);
	ev.put_in_game(9,9,2,SNOWMAN);
	ev.put_in_game(8,9,2,SNOWMAN);
	ev.put_in_game(8,8,2,SNOWMAN);
	ev.put_in_game(8,7,2,SNOWMAN);
	
	ev.put_in_game(8,11,2,SNOWMAN);
	ev.put_in_game(7,10,2,SNOWMAN);
	ev.put_in_game(7,9,2,SNOWMAN);
	ev.put_in_game(6,9,2,SNOWMAN);
	ev.put_in_game(5,8,2,SNOWMAN);
	ev.put_in_game(5,7,2,SNOWMAN);
*/
	for (int i = 11 ; i > 1 ; i--)
		for (int j = 11 ; j > 1 ; j--)
			ev.put_in_game(j,i,2,SNOWMAN);
	
	ob = new Destroy_All_Structures(RED);
}

void Kill_Snowmen::clean()
{	
	Level::clean();

	delete ob;
}

string Kill_Snowmen::get_level_name() 
{
	return "Kill The Snowmen!"; 
}

bool Kill_Snowmen::win()
{
	if (ob->has_been_completed())
	{
		set_winning_team(get_team(GREEN - 1));
		return true;
	}

	return false;
}
