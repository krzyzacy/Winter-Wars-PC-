#include "Claim_Tree_Level.h"
#include "Player_Claim_Tree_View.h"
#include "World.h"
#include "Tile.h"

using namespace std;

string Claim_Tree_Level::get_level_name()
{
	return "Claim_Tree_Level";
}

Player_View *Claim_Tree_Level::create_player_view(Player *p)
{
	return new Player_Claim_Tree_View(p);
}


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
		set_winning_team(get_team(get_center_tile()->get_team() - 1));
		return true;
	}
	return false;
}
