#include "Collision_Table.h"

#include "Game_Model.h"

#include "Collidable.h"
#include "Player.h"
#include "Permanent.h"
#include "Snowball.h"

#include <vector>
#include <zenilib.h>

using namespace std;
using namespace Zeni;

const int num_Obs_c = 3;

Collision_Table::Collision_Table()
	: table(num_Obs_c, vector<fxn_ptr_t>(num_Obs_c, (fxn_ptr_t)0))
{

	table.at(Snowball::snowball_ID_c).at(Collidable::collidable_ID_c) = 0;

	table.at(Snowball::snowball_ID_c).at(Snowball::snowball_ID_c) =
		(fxn_ptr_t)&Collision_Table::collideSnowballSnowball;

	table.at(Snowball::snowball_ID_c).at(Player::player_ID_c) = 
		(fxn_ptr_t)&Collision_Table::collideSnowballPlayer;
/*
	table.at(Snowball::snowball_ID_c).push_back(
		(fxn_ptr_t)&Collision_Table::collideSnowballPermanent);


*/
	
	table.at(Player::player_ID_c).push_back(NULL);

	table.at(Player::player_ID_c).at(Snowball::snowball_ID_c) =
		(fxn_ptr_t)&Collision_Table::collidePlayerSnowball;

	table.at(Player::player_ID_c).at(Player::player_ID_c) = 
		(fxn_ptr_t)&Collision_Table::collidePlayerPlayer;
/*
	table.at(Player::player_ID_c).push_back(
		(fxn_ptr_t)&Collision_Table::collidePlayerPermanent);


	/*
	
	table.at(Permanent::target_ID_c).push_back(NULL);

	table.at(Permanent::target_ID_c).push_back(
		(fxn_ptr_t)&Collision_Table::collidePermanentSnowball);

	table.at(Permanent::target_ID_c).push_back(
		(fxn_ptr_t)&Collision_Table::collidePermanentPlayer);

	table.at(Permanent::target_ID_c).push_back(
		(fxn_ptr_t)&Collision_Table::collidePermanentPermanent);		
*/
}


void Collision_Table::collideSnowballSnowball(Snowball* b1, Snowball* b2)
{

}

void Collision_Table::collidePlayerSnowball(Player* p1, Snowball* b1)
{	
   
}

void Collision_Table::collideSnowballPlayer(Snowball* b1, Player* p1)
{
	collidePlayerSnowball(p1,b1);
}

void Collision_Table::collidePlayerPlayer(Player* p1, Player* p2)
{
	// if no collision, return
//	if (!p1->body->intersects(p2->body) || p1 == p2)
//		return ;
	
}

void Collision_Table::collidePermanentSnowball(Permanent* w1, Snowball* ob2)
{	
	collideSnowballPermanent(ob2, w1);
}

void Collision_Table::collidePlayerPermanent(Player *ob2, Permanent *w1)
{	

}

void Collision_Table::collidePermanentPlayer(Permanent* w1, Player* ob2)
{
	collidePlayerPermanent(ob2, w1);
}

void Collision_Table::collideSnowballPermanent(Snowball *ob2, Permanent *w1)
{

}

void Collision_Table::collidePermanentPermanent(Permanent*, Permanent*)
{

}

