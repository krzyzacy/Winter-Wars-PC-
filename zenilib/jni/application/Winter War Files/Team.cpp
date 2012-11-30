#include "Team.h"
#include "World.h"
#include "Tile.h"
#include "Player.h"
#include "Game_Model.h"


using namespace std;
using namespace Zeni;


Team::Team(Tile* BaseTile)	:
	Base(BaseTile), Ice_Blocks(0), intake_rate(1.0), Team_Color(NEUTRAL)
{
	ResourceTime.start();
}


Team::~Team(void)
{
}

void Team::add_player(Player *p)	{
	members.push_back(p);
}

void Team::update()	{
	//First do stuff based on the network from the last step
	if(ResourceTime.seconds() > 1)	{
		Ice_Blocks += intake_rate;
		ResourceTime.reset();
	}
	intake_rate = 0;
	for(set<Tile*>::iterator it = Network.begin(); it != Network.end(); ++it)	{
		switch((*it)->get_covering())	{
		case SOFT_SNOW:
			intake_rate += 5;
			break;
		case HARD_SNOW:
			intake_rate += 3;
			break;
		case ICE:
			break;
		default:
			break;
		}
	}
	
	//check connectivity, updates the network and stuff, need base tile for this
	//other stuff
	//Go throught disconnected_tiles and make sure their structures are deactivated
}


void Team::set_Team_Color(TEAM_INDEX in)	{
	Team_Color = in;
}

void Team::add_tile(Tile *t)	{
	Network.insert(t);
	//do the stuff for add adjacent members(cycle through family and add
}

void Team::remove_tile(Tile *t)	{
	Network.erase(t);
	Adjacent_Tiles.erase(t);
	Disconnected_Tiles.erase(t);
}

bool Team::is_adjacent_to_network(Tile *t)	{
	return Adjacent_Tiles.count(t);
}

bool Team::is_in_network(Tile *t)	{
	return Network.count(t);
}

void Team::check_connectivity()	{

}
