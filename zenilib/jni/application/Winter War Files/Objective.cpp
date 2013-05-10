#include "Objective.h"
#include "Game_Model.h"

#include "Player.h"
#include "Team.h"
#include "World.h"
#include "Utility.h"
#include "Object_factory.h"
#include "Tile.h"
#include "Event.h"
#include "Snowball.h"

#include "Globals.h"

#include <list>

using namespace std;
using namespace Zeni;

Objective::Objective()
{
	message = "This string should never be seen";
}

Objective::~Objective()
{};

bool Objective::has_been_completed()
{	//Always returns false becuase base class is abstract
	return false;
}

Zeni::String Objective::get_message_to_display()
{
	return message;
}

Objective* Objective::get_next_Objective()
{
	return new Build_Structure(HEALING_POOL);
}

Objective* Build_Structure::get_next_Objective()
{
	return new Build_Other_Structures();
}

Objective* Build_Other_Structures::get_next_Objective()
{
	return new Throw_Snowball_At_Enemy();
}

Objective* Throw_Snowball_At_Enemy::get_next_Objective()
{
	return new Pack_Snowball();
}

Objective* Pack_Snowball::get_next_Objective()
{
	return new Scoop_Snow();
}

Objective* Scoop_Snow::get_next_Objective()
{
	return new Destroy_Structures();
}

Objective* Destroy_Structures::get_next_Objective()
{
	return new Raise_Lower_Tiles();
}

Objective* Raise_Lower_Tiles::get_next_Objective()
{
	return new Build_a_Chain_To_Tree();
}

Objective* Build_a_Chain_To_Tree::get_next_Objective()
{
	return new Destroy_Key_Enemy_Structures();
}

Objective* Destroy_Key_Enemy_Structures::get_next_Objective()
{
	return new Rescue_Your_Network();
}

Objective* Rescue_Your_Network::get_next_Objective()
{
	return new Claim_The_Tree();
}

Objective* Claim_The_Tree::get_next_Objective()
{
	return new Defend_Your_Claim();
}

Objective* Defend_Your_Claim::get_next_Objective()
{
	return NULL;
}

Build_Structure::Build_Structure(int type_) : type(type_)
{ message = "Build a " + Structure_Names[type] + " by right clicking towards the tile you want."; }

bool Build_Structure::has_been_completed()
{
	if (Game_Model::get().get_player(0)->get_team()->stats.structures[type]){
		return true;
	}		

	return false;
}

Build_Other_Structures::Build_Other_Structures()	{
	message = "Select other Structures with Q and Shift. Build one of each!"; 
	Build_Event ev;
	
	ev.put_in_game(10,12,2,2);
	ev.put_in_game(10,11,2,2);
	ev.put_in_game(10,10,2,1);
	ev.put_in_game(10,9,2,4);
	ev.put_in_game(10,8,2,3);
	ev.put_in_game(9,11,2,2);
	ev.put_in_game(9,10,2,4);
	ev.put_in_game(9,9,2,2);
	ev.put_in_game(8,9,2,2);
	ev.put_in_game(8,8,2,1);
	ev.put_in_game(8,7,2,2);
	
		
	//Old snow factory
	//ev.put_in_game(10,12,2,3);

	list<Tile*> tree_ring = Game_Model::get().get_World()->Get_Family(Game_Model::get().get_World()->get_center_Tile());
	for(list<Tile*>::iterator it = tree_ring.begin(); it != tree_ring.end(); ++it)	{
		create_structure(FORT, (*it), Game_Model::get().get_team(RED - 1));
	}


}

bool Build_Other_Structures::has_been_completed()
{	
	if (Game_Model::get().get_player(0)->get_team()->stats.structures[HEALING_POOL]
	&& Game_Model::get().get_player(0)->get_team()->stats.structures[FORT]
	&& Game_Model::get().get_player(0)->get_team()->stats.structures[SNOWMAN]
	&& Game_Model::get().get_player(0)->get_team()->stats.structures[SNOW_FACTORY]
	)
		return true;

	return false;
}

Throw_Snowball_At_Enemy::Throw_Snowball_At_Enemy()
{
	message = "Throw Snowballs with Left Mouse Button to defeat enemies!";
	Game_Model::get().add_player(create_player(Game_Model::get().get_team(RED-1), "Boy"
		, Game_Model::get().get_tile(6,5)));

	//Changed from 11 to 6, 5


	/*
	for(int i = 0; i < 10; i++){
		for(int j = 0; j < 10; j++){
			Snowball *sb = new Snowball(Game_Model::get().get_player(1),
				Point3f(50 * (i + 5), 50 * (j + 5), 1000), Vector3f(20, 20, 20));

			sb->get_thrown(Vector3f(0, 0, 0));

			Game_Model::get().add_moveable(sb);
		}
	}
	*/
}

bool Throw_Snowball_At_Enemy::has_been_completed()
{
	if (Game_Model::get().get_player(0)->stats.damage_dealt 
		&& Game_Model::get().get_player(1)->stats.damage_taken)
		return true;

	return false;
}

Pack_Snowball::Pack_Snowball()
{ message = "Hold the Left Mouse Button down to pack snow from your snow pouch and make a larger snowball"; }

bool Pack_Snowball::has_been_completed()
{
	if (Game_Model::get().get_player(0)->stats.num_large_snowballs)
		return true;

	return false;
}

Scoop_Snow::Scoop_Snow() :
	start_scooped(Game_Model::get().get_player(0)->stats.amount_scooped)
{
	message = "Hold E to scoop up snow and put it in your snow pouch, you must be on a soft snow tile";
}

bool Scoop_Snow::has_been_completed()
{
	if (Game_Model::get().get_player(0)->stats.amount_scooped > start_scooped)
		return true;

	return false;
}

Destroy_Structures::Destroy_Structures()
{
	message = "Destroy Enemy Stuctures by shooting snowballs at them";


}

bool Destroy_Structures::has_been_completed()
{
	return (Game_Model::get().get_player(0)->stats.destroyed > 0);
	//return false;
}

Raise_Lower_Tiles::Raise_Lower_Tiles()
{ message = "Press R and F to raise and lower tiles"; }

bool Raise_Lower_Tiles::has_been_completed()
{
	return Game_Model::get().get_player(0)->stats.tiles_lowered || 
		Game_Model::get().get_player(0)->stats.tiles_raised ;
}

Build_a_Chain_To_Tree::Build_a_Chain_To_Tree()
{ 
	message = "Connect a set of tiles from your base to the tree!";
}

bool Build_a_Chain_To_Tree::has_been_completed()
{
	return Game_Model::get().get_player(0)->stats.built > 6;
}

Destroy_Key_Enemy_Structures::Destroy_Key_Enemy_Structures()
{
	message = "Destroy key enemy structures that link the rest of their network to their base, and they will all disappear!";

	Build_Event ev;
	
	ev.put_in_game(10,12,2,2);
	ev.put_in_game(10,11,2,2);
	ev.put_in_game(10,10,2,1);
	ev.put_in_game(10,9,2,4);
	ev.put_in_game(10,8,2,3);
	ev.put_in_game(9,11,2,2);
	ev.put_in_game(9,10,2,4);
	ev.put_in_game(9,9,2,2);
	ev.put_in_game(8,9,2,2);
	ev.put_in_game(8,8,2,1);
	ev.put_in_game(8,7,2,2);
	
	list<Tile*> tree_ring = Game_Model::get().get_World()->Get_Family(Game_Model::get().get_World()->get_center_Tile());
	for(list<Tile*>::iterator it = tree_ring.begin(); it != tree_ring.end(); ++it)	{
		create_structure(FORT, (*it), Game_Model::get().get_team(RED - 1));
	}
}

bool Destroy_Key_Enemy_Structures::has_been_completed()
{
	if(Game_Model::get().get_team(RED-1)->territory_disconnected())	{
		isolation_survival_time = 0;
		return true;
	}

	return false;
}

Rescue_Your_Network::Rescue_Your_Network()	
	: snowballs_caused_disconnect(false)
{
	message = "The Enemy has disconnected part of your network from your base,\nreconnect it with Structures before it disappears!";

	list<Tile*> base_ring = Game_Model::get().get_World()->Get_Family(Game_Model::get().get_team(GREEN - 1)->get_base());
	for(list<Tile*>::iterator it = base_ring.begin(); it != base_ring.end(); ++it)	{
		for(int i = 0; i < 20; i++)	{
			Snowball *sb = new Snowball(Game_Model::get().get_player(1),
				(*it)->get_structure_base() + Point3f(0,0,500) , Vector3f(20, 20, 20));
			sb->get_thrown(Vector3f(0, 0, 0));
			Game_Model::get().add_moveable(sb);
		}
	}

	//like 20 days or so, should be plenty
	//isolation_survival_time = 1000000;


}

bool Rescue_Your_Network::has_been_completed()
{
	isolation_survival_time = 1000000;
	//First wait for the snowballs to drop and kill it
	//Then If they reconnect it move on
	if(Game_Model::get().get_team(GREEN - 1)->territory_disconnected())	{
		snowballs_caused_disconnect = true;
	}

	if(snowballs_caused_disconnect && !Game_Model::get().get_team(GREEN - 1)->territory_disconnected())	{
		parameters.find("Disappearance Wait Time").reset();
		return true;
	}

	return false;
}


Claim_The_Tree::Claim_The_Tree()	{
	message = "Build on the Tree to claim it for your team!";

	
}

bool Claim_The_Tree::has_been_completed()
{
	return Game_Model::get().get_team(GREEN - 1)->stats.structures[TREE];
}

Defend_Your_Claim::Defend_Your_Claim() 
	:claim_count(0)
{
	message = "Defend the tree for 20 seconds by destroying enemies next to it, or reclaiming it as your own!";

	Build_Event ev;
	
	ev.put_in_game(10,12,2,2);
	ev.put_in_game(10,11,2,2);
	ev.put_in_game(10,10,2,1);
	ev.put_in_game(10,9,2,4);
	ev.put_in_game(10,8,2,3);
	ev.put_in_game(9,11,2,2);
	ev.put_in_game(9,10,2,4);
	ev.put_in_game(9,9,2,2);
	ev.put_in_game(8,9,2,2);
	ev.put_in_game(8,8,2,1);
	ev.put_in_game(8,7,2,2);
	
	list<Tile*> tree_ring = Game_Model::get().get_World()->Get_Family(Game_Model::get().get_World()->get_center_Tile());
	for(list<Tile*>::iterator it = tree_ring.begin(); it != tree_ring.end(); ++it)	{
		create_structure(SNOWMAN, (*it), Game_Model::get().get_team(RED - 1));
	}

	wait_to_claim_tree.start();
	

}

bool Defend_Your_Claim::has_been_completed()
{//represents win?
	if(wait_to_claim_tree.seconds() > 5)	{
		create_structure(TREE, Game_Model::get().get_World()->get_center_Tile(), Game_Model::get().get_team(RED - 1));
		wait_to_claim_tree.reset();
		wait_to_claim_tree.stop();
	}

	return false;
}