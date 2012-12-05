#include "Snowman.h"
#include "Team.h"

using namespace std;
using namespace Zeni;

Snowman::Snowman(Team *team, Tile* tile_,
				const Zeni::Point3f &base_) :
	Structure(team, tile_, base_)
{
	center.z -= 8;
	create_body();
	Health = Struct_Integrity[SNOWMAN];
}


Snowman::~Snowman(void)
{
}

void Snowman::update(const float &time)
{
	Structure::update(time);
}

const model_key_t Snowman::get_model_name() const 
{
	switch(owner->get_Team_Index())	{
	case BLUE:
		return ("blue_snowman");
	case GREEN:
		return ("green_snowman");
	case RED:
		return ("red_snowman");
	case ORANGE:
		return ("orange_snowman");
	default:
		return ("blue_snowman");
		break;
	}
}

void Snowman::create_body()		{
	Point3f Top = Seen_Object::get_top_center();
	Point3f Bot = Seen_Object::get_bottom_center();
	body = Zeni::Collision::Capsule(Top, Bot, size.z/4);
}