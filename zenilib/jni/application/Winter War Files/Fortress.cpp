#include "Fortress.h"

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
	return "fortress";
}