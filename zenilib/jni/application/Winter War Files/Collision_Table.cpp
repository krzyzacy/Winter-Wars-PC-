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

const int num_Obs_c = 4;

Collision_Table::Collision_Table()
	: table(num_Obs_c, vector<fxn_ptr_t>())
{
/*
	table.at(Snowball::snowball_ID_c).push_back(NULL);

	table.at(Snowball::snowball_ID_c).push_back(
		(fxn_ptr_t)&Collision_Table::collideBB);

	table.at(Snowball::snowball_ID_c).push_back(
		(fxn_ptr_t)&Collision_Table::collideBP);

	table.at(Snowball::snowball_ID_c).push_back(
		(fxn_ptr_t)&Collision_Table::collideBW);



	
	table.at(Player::player_ID_c).push_back(NULL);

	table.at(Player::player_ID_c).push_back(
		(fxn_ptr_t)&Collision_Table::collidePB);

	table.at(Player::player_ID_c).push_back(
		(fxn_ptr_t)&Collision_Table::collidePP);

	table.at(Player::player_ID_c).push_back(
		(fxn_ptr_t)&Collision_Table::collidePW);



	
	table.at(Permanent::target_ID_c).push_back(NULL);

	table.at(Permanent::target_ID_c).push_back(
		(fxn_ptr_t)&Collision_Table::collideWB);

	table.at(Permanent::target_ID_c).push_back(
		(fxn_ptr_t)&Collision_Table::collideWP);

	table.at(Permanent::target_ID_c).push_back(
		(fxn_ptr_t)&Collision_Table::collideWW);		
*/
}


void Collision_Table::collideBB(Snowball* b1, Snowball* b2)
{

}

void Collision_Table::collidePB(Player* p1, Snowball* b1)
{	
   
}

void Collision_Table::collideBP(Snowball* b1, Player* p1)
{
	collidePB(p1,b1);
}

void Collision_Table::collidePP(Player* , Player* )
{

}

void Collision_Table::collideWB(Permanent* w1, Snowball* ob2)
{	
	collideBW(ob2, w1);
}

void Collision_Table::collidePW(Player *ob2, Permanent *w1)
{	

}

void Collision_Table::collideWP(Permanent* w1, Player* ob2)
{
	collidePW(ob2, w1);
}

void Collision_Table::collideBW(Snowball *ob2, Permanent *w1)
{

}

void Collision_Table::collideWW(Permanent*, Permanent*)
{

}

