#include "Team.h"
#include "World.h"
#include "Tile.h"
#include "Player.h"
#include "Structure.h"
#include "Game_Model.h"
#include "Object_factory.h"


using namespace std;
using namespace Zeni;


Team::Team(Tile* BaseTile)	:
	Base(BaseTile), Ice_Blocks(1000), intake_rate(1), Team_Color(NEUTRAL)
{
	ResourceTime.start();
}


Team::~Team(void)
{
}
// returns null if index == number of players
Player *Team::get_player(int index)
{
	if (index >= members.size())
		return NULL;

	return members.at(index);
}

void Team::add_player(Player *p)	{
	members.push_back(p);
	p->set_Team(this);
}

Point3f Team::get_spawn_point()	const	{
	float x = rand()%20;
	float y = rand()%20;
	Point3f Spawn = Base->get_structure_base();
	Spawn.x += x;
	Spawn.y += y;
	Spawn.z += 150;
	return Spawn;
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
			intake_rate += 50;
			break;
		case HARD_SNOW:
			intake_rate += 30;
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
	add_tile(Base);
	Base->set_covering(SOFT_SNOW);
	Base->set_team(Team_Color);
	Game_Model::get().add_structure(create_structure(HEALING_POOL, Base, this));
}

void Team::add_tile(Tile *t)	{
	Network.insert(t);
	//do the stuff for add adjacent members(cycle through family and add
	World *w = Game_Model::get().get_World();
	list<Tile*> family = w->Get_Family(t);
	for(list<Tile*>::iterator it = family.begin(); it != family.end(); it++)
		Adjacent_Tiles.insert(*it);
}

void Team::remove_tile(Tile *t)	{
	Network.erase(t);
	Adjacent_Tiles.erase(t);
	Disconnected_Tiles.erase(t);
}

bool Team::tile_is_ready(Tile * cand, int type)	{
			//If nothing has been built on it, (no one owns it), 
	//is adjacent to your network, and have enough ice blocks
	//If you already own this tile, then it assumes you are switching the building type
	if(is_in_network(cand))	{
		cand->destroy_structure();
		return true;
	}
	//Do a check here for the center tile
	//Return false if you can build on it because don't want to let game_obejct create structure


	//This code handles neutral tiles and enemy tiles
	if(!cand->has_building() && is_adjacent_to_network(cand))	{
		if(Ice_Blocks >= Build_Cost[type])	{	//Structure cost	
			Ice_Blocks -= Build_Cost[type];
			add_tile(cand);
			return true;
		}
	}
	return false;
}

bool Team::is_adjacent_to_network(Tile *t)	{
	return Adjacent_Tiles.count(t);
}

bool Team::is_in_network(Tile *t)	{
	return Network.count(t);
}

void Team::check_connectivity()	{

}
