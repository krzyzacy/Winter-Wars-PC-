#include "Fortress.h"
#include "Team.h"
#include "Player.h"

using namespace std;
using namespace Zeni;

Fortress::Fortress(Team *team, Tile* tile_,
				const Zeni::Point3f &base_) :
	Structure(team, tile_, base_)
{
	center.z += 26;
	create_body();
	Health = Struct_Integrity[FORT];
	animation_state = new Fort_spin();
}

Fortress::~Fortress(void)
{
}

void Fortress::handle_player_collision(Player *P)
{
	if (P->get_team() != owner)
		Structure::handle_player_collision(P);
}

void Fortress::update(const float &time)
{
	Structure::update(time);
}

const model_key_t Fortress::get_model_name() const 
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

void Fortress::create_body()		{
	Point3f Top = Seen_Object::get_top_center();
	Point3f Bot = Seen_Object::get_bottom_center();
	body = Zeni::Collision::Capsule(Top, Bot, size.z/2 + 3);
}

Animator *Fortress::get_animator() const
{
	return animation_state;
}