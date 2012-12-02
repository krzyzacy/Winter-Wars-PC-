#include "Snowman.h"
#include "Team.h"

Snowman::Snowman(Team *team, Tile* tile_,
				const Zeni::Point3f &base_) :
	Structure(team, tile_, base_)
{
	center.z -= 8;
}


Snowman::~Snowman(void)
{
}

void Snowman::update(const float &time)
{

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