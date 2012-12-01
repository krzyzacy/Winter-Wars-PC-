#include "Healing_Pool.h"
#include "Team.h"

Healing_Pool::Healing_Pool(Team *team,
			const Zeni::Point3f &position_) :
	Structure(team, position_)
{
}


Healing_Pool::~Healing_Pool(void)
{
}

void Healing_Pool::update(const float &time)
{

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