#include "Collision_Table.h"

#include "Game_Model.h"

#include "Collidable.h"
#include "Player.h"
#include "Structure.h"
#include "Snowball.h"

#include <vector>
#include <zenilib.h>

using namespace std;
using namespace Zeni;

const int num_Obs_c = 4;

Collision_Table::Collision_Table()
	: table(num_Obs_c, vector<fxn_ptr_t>(num_Obs_c, (fxn_ptr_t)0))
{
	collided = false;
	table.at(Snowball::snowball_ID_c).at(Collidable::collidable_ID_c) = 0;

	table.at(Snowball::snowball_ID_c).at(Snowball::snowball_ID_c) =
		(fxn_ptr_t)&Collision_Table::collideSnowballSnowball;

	table.at(Snowball::snowball_ID_c).at(Player::player_ID_c) = 
		(fxn_ptr_t)&Collision_Table::collideSnowballPlayer;

	table.at(Snowball::snowball_ID_c).at(Structure::structure_ID_c) = 
		(fxn_ptr_t)&Collision_Table::collideSnowballStructure;



	
	table.at(Player::player_ID_c).at(Collidable::collidable_ID_c) = 0;

	table.at(Player::player_ID_c).at(Snowball::snowball_ID_c) =
		(fxn_ptr_t)&Collision_Table::collidePlayerSnowball;

	table.at(Player::player_ID_c).at(Player::player_ID_c) = 
		(fxn_ptr_t)&Collision_Table::collidePlayerPlayer;

	table.at(Player::player_ID_c).at(Structure::structure_ID_c) = 
		(fxn_ptr_t)&Collision_Table::collidePlayerStructure;



	
	table.at(Structure::structure_ID_c).at(Collidable::collidable_ID_c) = 0;

	table.at(Structure::structure_ID_c).at(Player::player_ID_c) = 
		(fxn_ptr_t)&Collision_Table::collideStructureSnowball;

	table.at(Structure::structure_ID_c).at(Snowball::snowball_ID_c) = 
		(fxn_ptr_t)&Collision_Table::collideStructurePlayer;

	table.at(Structure::structure_ID_c).at(Structure::structure_ID_c) = 
		(fxn_ptr_t)&Collision_Table::collideStructureStructure;		

}


void Collision_Table::collideSnowballSnowball(Snowball* b1, Snowball* b2)
{

}

void Collision_Table::collidePlayerSnowball(Player* p1, Snowball* b1)
{	
   	//if no collision, return
	if (!p1->body.intersects(b1->body) || b1->owner == p1)
		return;

	p1->get_damaged(b1->deal_damage());

}

void Collision_Table::collideSnowballPlayer(Snowball* b1, Player* p1)
{
	collidePlayerSnowball(p1,b1);
}

void Collision_Table::collidePlayerPlayer(Player* p1, Player* p2)
{
	//if no collision, return
	if (!p1->body.intersects(p2->body) || p1 == p2)
		return;

	p1->push_away_from(p2->center, 200);
	p2->push_away_from(p1->center, 200);
}

void Collision_Table::collideStructureSnowball(Structure* w1, Snowball* ob2)
{	
	collideSnowballStructure(ob2, w1);
}

void Collision_Table::collidePlayerStructure(Player *ob2, Structure *w1)
{	
	//Do structure collision resolution here, need to work on that bounce back function
	/*Vector3f rebound(ob2->center - w1->center);
	rebound.z = 0;
	ob2->accelerate(800 * rebound, Game_Model::get().get_time_step());*/
	if(!ob2->body.intersects(w1->body))
		return;

	ob2->push_away_from(w1->center, 10);
}

void Collision_Table::collideStructurePlayer(Structure* w1, Player* ob2)
{
	collidePlayerStructure(ob2, w1);
}

void Collision_Table::collideSnowballStructure(Snowball *ob2, Structure *w1)
{
	//Basically damage the structure, other than that, meh
	if (!ob2->body.intersects(w1->body))
		return;

	w1->receive_hit(ob2);
}

void Collision_Table::collideStructureStructure(Structure*, Structure*)
{
	//WAT. This cannot happen
}

