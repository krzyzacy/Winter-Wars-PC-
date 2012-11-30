#include "Healing_Pool.h"


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
	return "healingpool";
}