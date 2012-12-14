#include "Collision_Table.h"

#include "Game_Model.h"
#include "World.h"

#include "Collidable.h"
#include "Player.h"
#include "Structure.h"
#include "Snowball.h"
#include "Team.h"
#include "Effect.h"

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

	if (b1->damage_dealt)
		return;


	//*// Friendly Fire
	if (p1->get_team() == b1->team)
	{
		if (b1->owner) // not a snowman
			b1->owner->stats.friendly_hit++;	

		if (!b1->owner) // <-comment out for all friendly fire to go through
			return;  // just pass through if thrown by snowman
	}
	//*/


	// if the player's dead, don't continue
	if (p1->is_player_KO())
		return;
	
	//If we want to stop the snowball, move this above friendly fire
	float damage_dealt = b1->deal_damage();  
	
	p1->get_damaged(damage_dealt);

	Game_Model::get().add_effect(new Effect("explode", b1->center, Vector3f(10,10,10)*b1->size.z/4));

	// if snowman shot it, don't add player stats
	if (!b1->owner)
		return;

	// tell the player that threw the ball that he made a hit
	b1->owner->stats.hit++;
	b1->owner->stats.damage_dealt += damage_dealt;

	// he killed the player
	if (p1->is_player_KO() )
		b1->owner->stats.kills++;
	
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
	//Structure player collision resolution
	
	w1->handle_player_in_range(ob2->myTeam, ob2->body);

	if(!ob2->body.intersects(w1->body))
		return;
	w1->handle_player_collision(ob2);
}

void Collision_Table::collideStructurePlayer(Structure* w1, Player* ob2)
{
	collidePlayerStructure(ob2, w1);
}

void Collision_Table::collideSnowballStructure(Snowball *b2, Structure *w1)
{

	if(Game_Model::get().get_World()->get_tile(w1->get_bottom_center()) == Game_Model::get().get_World()->get_center_Tile())
		return;

	if (!b2->body.intersects(w1->body))
		return;
	
	if (b2->damage_dealt)
		return;
	
	if (w1->Status == DESTROYED || b2->team == w1->owner)
		return;

	int damage = b2->deal_damage();

	w1->receive_hit(damage);

	Game_Model::get().get_player(1)->play_sound();
	Game_Model::get().add_effect(new Effect("explode", b2->center, Vector3f(10,10,10)*b2->size.z/4));

	if (!b2->owner)  //snowmen should damage other structures
		return;		// but no stats
	
	b2->owner->stats.hit++;
	b2->owner->stats.damage_dealt += damage;
	
	if (w1->Status == DESTROYED)
		b2->owner->stats.destroyed++;
}

void Collision_Table::collideStructureStructure(Structure*, Structure*)
{
	//WAT. This cannot happen
	// Explode Everything!
}

