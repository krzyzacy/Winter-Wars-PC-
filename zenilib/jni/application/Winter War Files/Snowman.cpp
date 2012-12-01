#include "Snowman.h"
#include "Team.h"

Snowman::Snowman(Team *team,
			const Zeni::Point3f &position_) :
	Structure(team, position_)
{
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