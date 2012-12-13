#include "Team.h"
#include "World.h"
#include "Tile.h"
#include "Player.h"
#include "Structure.h"
#include "Game_Model.h"
#include "Object_factory.h"

const int Max_Resources = 15000;

using namespace std;
using namespace Zeni;

Team::Team(Tile* BaseTile)	:
	Base(BaseTile), Ice_Blocks(1000), intake_rate(1), Team_Color(NEUTRAL), 
	network_unstable(false)
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
	if(Base->get_covering() != SOFT_SNOW)
		Base->set_covering(SOFT_SNOW);

	if(network_unstable)	{
		check_connectivity();
		Deactivate_disconnected();
		reintegrate_connected();
		network_unstable = false;
	}

	if (!Disconnected_Tiles.empty())
	{
		message_team("ALERT: YOUR TERRITORY IS DISCONNECTED! Link it together with a structure", 10);
	}

	if(ResourceTime.seconds() > 1)	{
		Ice_Blocks += intake_rate;
		if(Ice_Blocks >= Max_Resources)
			Ice_Blocks = Max_Resources;
		ResourceTime.reset();
	
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
	}
	
}

void Team::message_team(const String &message, int priority)
{
	for (int i = 0 ; i < members.size() ; i++)
	{
		get_player(i)->add_message(message, priority);
	}
}

void Team::set_Team_Color(TEAM_INDEX in)	{
	Team_Color = in;
	add_tile(Base);
	Base->set_covering(SOFT_SNOW);
	Base->set_team(Team_Color);
	Game_Model::get().add_structure(create_structure(BASE, Base, this));
}

void Team::add_tile(Tile *t)	{
	Network.insert(t);
	Adjacent_Tiles.insert(t);
	network_unstable = true;
	//do the stuff for add adjacent members(cycle through family and add
	World *w = Game_Model::get().get_World();
	list<Tile*> family = w->Get_Family(t);
	for(list<Tile*>::iterator it = family.begin(); it != family.end(); it++)	{
		Adjacent_Tiles.insert(*it);
		if(Disconnected_Tiles.count(*it))	{
			//if one of the adjacent tiles was disconnected then, it might have reconnected the others
			network_unstable = true;
		}
	}
}

void Team::remove_tile(Tile *t)	{
	if(t == Base)	{
		t->set_team(Team_Color);
		return;
	}

	Network.erase(t);
	Disconnected_Tiles.erase(t);
	network_unstable = true;
}

bool Team::tile_is_ready(Tile * cand, int type)	{
	if(!is_adjacent_to_network(cand))
	{
		
		message_team("Error: Can only build on tiles next to your active territory!");
		return false;
	}

	if(cand == Base)
	{
		message_team("Error: Can't build on Base!");
		return false;
	}

			//If nothing has been built on it, (no one owns it), 
	//is adjacent to your network, and have enough ice blocks
	//If you already own this tile, then it assumes you are switching the building type
	if(is_in_network(cand) && cand != Game_Model::get().get_World()->get_center_Tile())	{
		cand->destroy_structure();
		return true;
	}

	//You can't build on boundary tiles
	if(Game_Model::get().get_World()->is_boundary_tile(cand))
	{
		message_team("Error: Can't build on boundary cliffs!");
		return false;
	}

	//Do a check here for the center tile
	//Return false if you can build on it because don't want to let game_obejct create structure
	if(Game_Model::get().get_World()->get_center_Tile() == cand)	{
		//%%%%% Install something related to victory conditions here
		
		if(Network.count(cand) == 0)	{//Doesn't care about who has it currently, any can claim it
			//cand->get_building()->begin_isolation();
			if(cand->get_building()->get_team_pt() != 0)
				cand->get_building()->get_team_pt()->remove_tile(cand);

			cand->destroy_structure();
			add_tile(cand);
			Game_Model::get().add_structure(create_structure(TREE, cand, this));
			//cand->set_team(Team_Color);
			Start_Victory_Countdown();
		}
		return false; //becasue tree isn't an option to build
	}


	//This code handles neutral tiles and enemy tiles
	if(!cand->has_building())	{
		if(Ice_Blocks >= Build_Cost[type])	{	//Structure cost	
			Ice_Blocks -= Build_Cost[type];
			add_tile(cand);
			return true;
		}
		else
		{
			message_team("Error: Not enough Money to Build!");
			return false;
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
	//Current system
	//While(changed something)
		//changed something = false
		//Iterate through Owned Tiles
			//if OwnedTiles@(current)->family ->has member in connected set
				//Add OwnedTiles@(current) to connected set
				//Change =  true
		//Remove connected tiles we added from Owned Tiles set
	//End While

	//Alt version iterate through the connected set, which starts with base - intriguiing
	//Start with connected set, and if a family member is owned by this team, then add it and iterate again
	//well connected optimization
	set<Tile*> connected;
	connected.insert(Base);
	Network.erase(Base);
	//Add all disconnected tiles to netwrok, because they have this teams ownership, but aren't connected
	for(set<Tile*>::iterator dit = Disconnected_Tiles.begin(); dit != Disconnected_Tiles.end(); ++dit)	
		Network.insert(*dit);

	bool graph_changed = true;
	World* W = Game_Model::get().get_World();
	//This is the first way mentioned above
	while(graph_changed)	{
		graph_changed = false;
		list<Tile*> changes;	//Tiles that are now in connected set
		//Go through tiles that team is aware of as owning
		for(set<Tile*>::iterator it = Network.begin(); it != Network.end(); ++it)	{
			//Get the family of each owned tile
			list<Tile*> fam = W->Get_Family(*it);
			for(list<Tile*>::iterator fit = fam.begin(); fit != fam.end(); ++fit)	{
				//If anyone in the family of this owned tile is connected to the base, then so is this tile
				if(connected.count(*fit))	{
					changes.push_back(*it);
					connected.insert(*it);
					graph_changed = true;	
					//The graph of connected tiles changed, so need to loop through any owned tiles again
					//break;
					//break because if one of the family member is in connected that's enough
				}
			}
		}
		//To remove those connected to base from network, because they are uninteresting now.
		for(list<Tile*>::iterator cit = changes.begin(); cit != changes.end(); ++cit)		{
			Network.erase(*cit);
		}
		changes.clear();
	}

	//Resolution
		//At this point anything left in Network represents disconnected tiles
		//Connected reresents the tiles connected to the base


	Disconnected_Tiles.clear();
	Disconnected_Tiles = Network;
	Adjacent_Tiles.clear();
	Network = connected;
	
	//Goes through all connected tiles and says that the ones next to them are adjacent, 
	//Prevents you from building on places that are no longer adjacent, but once were
	for(set<Tile*>::iterator it = Network.begin(); it != Network.end(); ++it)	{
		list<Tile*> family = W->Get_Family(*it);
		Adjacent_Tiles.insert(*it);
		for(list<Tile*>::iterator fit = family.begin(); fit != family.end(); ++fit)	
			Adjacent_Tiles.insert(*fit);
	}

}

void Team::Deactivate_disconnected()	{
	for(set<Tile*>::iterator it = Disconnected_Tiles.begin(); it != Disconnected_Tiles.end(); ++it)		{
		if((*it)->has_building())
			(*it)->get_building()->begin_isolation();
	}
}

void Team::reintegrate_connected()	{	//Currently not in use because instantly destroyed
	for(set<Tile*>::iterator it = Network.begin(); it != Network.end(); ++it)		{
		if((*it)->has_building())
			(*it)->get_building()->reintegrate();
	}
}

void Team::Start_Victory_Countdown()	{
	WinTimer.start();
}

void Team::Stop_Victory_Countdown()	{
	WinTimer.stop();
	WinTimer.reset();
}
	
bool Team::win()
{
	if (time_till_win() <= 0)
		return true;
	return false;
}

float Team::time_till_win()
{
	return 20 - WinTimer.seconds();
}


bool Team::Is_Tree_Claimed()	{
	return Network.count(Game_Model::get().get_World()->get_center_Tile());
}

String Team::get_name()
{
	switch(get_Team_Index()){
		case GREEN:
			return "green";
			break;

		case RED:
			return "red";
			break;

		case BLUE:
			return  "blue";
			break;

		case ORANGE:
			return "orange";
			break;

		default:
			break;
	}
}

String Team::get_name_Upper_Case()
{
		switch(get_Team_Index()){
		case GREEN:
			return "Green";
			break;

		case RED:
			return "Red";
			break;

		case BLUE:
			return  "Blue";
			break;

		case ORANGE:
			return "Orange";
			break;

		default:
			break;
	}
}