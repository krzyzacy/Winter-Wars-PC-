#include "Snow_Factory.h"
#include "Team.h"

Snow_Factory::Snow_Factory(Team *team, Tile* tile_,
				const Zeni::Point3f &base_) :
	Structure(team, tile_, base_)
{
}


Snow_Factory::~Snow_Factory(void)
{
}

void Snow_Factory::update(const float &time)
{

}

const model_key_t Snow_Factory::get_model_name() const 
{
		switch(owner->get_Team_Index())	{
	case BLUE:
		return ("blue_snowfactory");
	case GREEN:
		return ("green_snowfactory");
	case RED:
		return ("red_snowfactory");
	case ORANGE:
		return ("orange_snowfactory");
	default:
		return ("blue_snowfactory");
		break;
	}
}