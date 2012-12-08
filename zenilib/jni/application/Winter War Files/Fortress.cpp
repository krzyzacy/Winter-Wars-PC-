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
	switch(owner->get_Team_Index())	{
	case BLUE:
		return ("blue_fort");
	case GREEN:
		return ("green_fort");
	case RED:
		return ("red_fort");
	case ORANGE:
		return ("orange_fort");
	default:
		return ("blue_fort");
		break;
	}
}

void Fortress::create_body()		{
	Point3f Top = Seen_Object::get_top_center();
	Point3f Bot = Seen_Object::get_bottom_center();
	body = Zeni::Collision::Capsule(Top, Bot, size.z/2 + 3);
}

