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


	collided = true;

	//p1->accelerate(Vector3f(0,0,1)*40, Game_Model::get().get_time_step());
	p1->accelerate(50*Vector3f(p1->center - p2->center), Game_Model::get().get_time_step());
//	p1->center = p1->center - 2*(p2->center - p1->center);
//	p2->center = p2->center + 2*(p2->center - p1->center);

}

void Collision_Table::collideStructureSnowball(Structure* w1, Snowball* ob2)
{	
	collideSnowballStructure(ob2, w1);
}

void Collision_Table::collidePlayerStructure(Player *ob2, Structure *w1)
{	

}

void Collision_Table::collideStructurePlayer(Structure* w1, Player* ob2)
{
	collidePlayerStructure(ob2, w1);
}

void Collision_Table::collideSnowballStructure(Snowball *ob2, Structure *w1)
{

}

void Collision_Table::collideStructureStructure(Structure*, Structure*)
{

}

