#include "Fortress.h"
#include "Team.h"

Fortress::Fortress(Team *team,
			const Zeni::Point3f &position_) :
	Structure(team, position_)
{
}

Fortress::~Fortress(void)
{
}

void Fortress::update(const float &time)
{

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