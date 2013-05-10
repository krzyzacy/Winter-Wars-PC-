#include "Team.h"
#include "World.h"
#include "Tile.h"
#include "Player.h"
#include "Structure.h"
#include "Game_Model.h"
#include "Object_factory.h"

float Max_Resources = 15000;
float starting_resources = 2000;
float hard_snow_intake = 30;
float soft_snow_intake = 50; 
float ice_intake = 0;

using namespace std;
using namespace Zeni;

Team::Team(Tile* BaseTile)	:
	Base(BaseTile), Ice_Blocks(starting_resources), intake_rate(0), Team_Color(NEUTRAL), 
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
	float x = rand()%5;
	float y = rand()%5;
	Point3f Spawn = Base->get_structure_base();
	Spawn.x += x;
	Spawn.y += y;
	Spawn.z += 150;

	return Spawn;
}

int Team::get_Player_Kills() {
	int team_kills = 0;
	for_each(members.begin(), members.end(), 
		     [&team_kills](Player* p)
	         { team_kills += p->stats.kills; });
	return team_kills;
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

	if (territory_disconnected())
	{
		message_team("ALERT: YOUR TERRITORY IS DISCONNECTED! Link it together with a structure", 100);
	}	
	else if (Is_Tree_Claimed())
	{
		message_team("Your team claimed the Tree! Protect your network for 20 seconds!", 3);
	}
	else if (is_adjacent_to_network(Game_Model::get().get_World()->get_center_Tile()))
	{
		message_team("You are adjacent to the Tree! Build on it to claim it!");
	}


	if(ResourceTime.seconds() > 1)	{
		Ice_Blocks += intake_rate;


		stats.total_resources += intake_rate;



		if(Ice_Blocks >= Max_Resources)
			Ice_Blocks = Max_Resources;
		ResourceTime.reset();

		intake_rate = 0;
		for(set<Tile*>::iterator it = Network.begin(); it != Network.end(); ++it)	{
			switch((*it)->get_covering())	{
			case SOFT_SNOW:
				intake_rate += soft_snow_intake;
				break;
			case HARD_SNOW:
				intake_rate += hard_snow_intake;
				break;
			case ICE:
				intake_rate += ice_intake;
				break;
			default:
				break;
			}

			// increment intake rate if it is a snow factory
			if((*it)->get_building())
				intake_rate += (*it)->get_building()->get_intake();

		}
	}

	stats.final_network = Network.size();

	if (stats.final_network > stats.largest_network)
		stats.largest_network = stats.final_network;

	stats.save_to_history();
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
	create_structure(BASE, Base, this);
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

	stats.tiles_lost++;
}

bool Team::allowed_to_build_on_Tile(Tile* cand)	{
	//Check for illegal tiles, base, boundary and not adjacent
	if(cand == Base)	
		throw Error("Error: Can't build on Base!");
	if(Game_Model::get().get_World()->is_boundary_tile(cand))	
		throw Error("Error: Can't build on boundary cliffs!");
	if(!is_adjacent_to_network(cand))	
		throw Error("Error: Can only build on tiles next to your active territory!");

	//Do a check to see if cand is the tree
	if(cand->has_building() && cand->get_building()->get_type() == TREE)	{
		if(Network.count(cand) == 0)	//If you do not have the tree
			return true;
		return false;	//If you do have the tree, you can't build on it again		
	}

	//At this point, you know it's not the tree, not an illegal tile, so if it's in
	//your network you can build on it
	if(is_in_network(cand))	
		return true;

	//At this point, you know it's not in your network and it's a legal tile 
	if(cand->has_building()) //Someone else has built on it
		return false;

	//You know it's a legal tile, no one else has it, it's not the tree, so if it's adj your good
	if(is_adjacent_to_network(cand))
		return true;

	//Should never get here, but if it does it isn't legal
	return false;
}

bool Team::can_afford_building(int type)	{
	if(Ice_Blocks >= Build_Cost[type])	
		return true;
	else	{
		throw Error("Error: Not enough Money to Build!");
		return false;
	}
}

void Team::pay_for_building(Structure* st)	{
	Ice_Blocks -= Build_Cost[st->get_type()];
	stats.resources_spent += Build_Cost[st->get_type()];
}

/*
* Assumes that allowed to build on tile is true
*/
void Team::add_tile_to_team_network(Tile* cand)	{
	//different behavior for center tile
	if(cand->has_building() && cand->get_building()->get_type() == TREE)	{
		//if some one else has it, kindly remove it from their network
		if(cand->get_building()->get_team_pt() != 0)	{
			cand->get_building()->get_team_pt()->remove_tile(cand); 
		}
		Start_Victory_Countdown();
	}


	add_tile(cand);


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

/*True if this team has the tree*/
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

void Team::modify_resources(int amt)
{
	Ice_Blocks += amt;

	if(Ice_Blocks >= Max_Resources)
			Ice_Blocks = Max_Resources;
}

int Team::take_resources(int amt)
{
	if (amt > Ice_Blocks)
	{
		int result = Ice_Blocks;
		Ice_Blocks = 0;
		return result;
	}

	Ice_Blocks -= amt;
	return amt;
}

Team::Team_Stats::Team_Stats() :
	Stats("Team"),
			total_resources(0), largest_network(0), 
			tiles_lost(0), final_network(0), resources_spent(0)
{
	add_stat("Total Resources", &total_resources);
	add_stat("Largest Network", &largest_network);
	add_stat("Tiles Lost", &tiles_lost);
	add_stat("Final Network", &final_network);
	add_stat("Resources_Spent", &resources_spent);

	for (int i = 0 ; i < NUM_STRUCTURES ; i++)
	{
		structures[i] = 0;
		add_stat(Structure_Names[i].std_str() + "'s Built", &structures[i]);
	}
}

bool Team::territory_disconnected()	{
	return !Disconnected_Tiles.empty();
}

