#include "Healing_Pool.h"
#include "Team.h"

using namespace std;
using namespace Zeni;

Healing_Pool::Healing_Pool(Team *team, Tile* tile_,
				const Zeni::Point3f &base_) :
	Structure(team, tile_, base_)
{
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

const model_key_t Healing_Pool::get_model_name() const 
{
	switch(owner->get_Team_Index())	{
	case BLUE:
		return ("blue_healingpool");
	case GREEN:
		return ("green_healingpool");
	case RED:
		return ("red_healingpool");
	case ORANGE:
		return ("orange_healingpool");
	default:
		return ("blue_healingpool");
		break;
	}
}

void Healing_Pool::create_body()		{
	Point3f Top = Seen_Object::get_top_center();
	Top.z - 10;
	Point3f Bot = Seen_Object::get_bottom_center();
	body = Zeni::Collision::Capsule(Top, Bot, size.z/2);
}