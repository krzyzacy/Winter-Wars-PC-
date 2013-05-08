#include "Claim_Tree_Level.h"
#include "World.h"
#include "Tile.h"

using namespace std;

void Claim_Tree_Level::start_up(const vector<Player_info*> &player_info)
{
	Level::start_up(player_info);
	
	// Place Tree  // maybe should go here
//	add_structure(create_structure(TREE, world->get_center_Tile(), NULL));
	
}

void Claim_Tree_Level::update()
{
	Level::update();
}

// returns true if some team has won
bool Claim_Tree_Level::win()
{
	if (time_till_win() <= 0)
	{
		stop();
		set_winning_team(get_team(get_center_tile()->get_team() - 1));
		return true;
	}
	return false;
}
