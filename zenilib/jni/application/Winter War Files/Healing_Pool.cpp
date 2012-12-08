#include "Healing_Pool.h"
#include "Team.h"
#include "Player.h"
#include "Game_Model.h"

using namespace std;
using namespace Zeni;

const float Healing_rate = 30;

Healing_Pool::Healing_Pool(Team *team, Tile* tile_,
				const Zeni::Point3f &base_) :
	Structure(team, tile_, base_)
{
	animation_state = new Pool_heal();
	center.z -= 22;
	create_body();
	Health = Struct_Integrity[HEALING_POOL];
}


Healing_Pool::~Healing_Pool(void)
{
}

void Healing_Pool::update(const float &time)
{
	Structure::update(time);
}

void Healing_Pool::handle_player_collision(Player *P)	{
//	switch_state(POOL_HEAL);
	P->healing_waters(Healing_rate * Game_Model::get().get_time_step());
}

const model_key_t Healing_Pool::get_model_name() const 
{
	string Teamname;
	switch(owner->get_Team_Index())	{
	case BLUE:
		Teamname = "blue";
		break;
	case GREEN:
		Teamname = "green";
		break;
	case RED:
		Teamname = "red";
		break;
	case ORANGE:
		Teamname = "orange";
		break;
	default:
		Teamname = "blue";
		break;
	}
	return Teamname + animation_state->get_model_name();
}

void Healing_Pool::create_body()		{
	Point3f Top = Seen_Object::get_top_center();
	Top.z - 10;
	Point3f Bot = Seen_Object::get_bottom_center();
	body = Zeni::Collision::Capsule(Top, Bot, size.z/2);
}

Animator *Healing_Pool::get_animator() const
{
	return animation_state;
}