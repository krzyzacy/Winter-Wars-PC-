#include "Claim_Tree_Level.h"

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