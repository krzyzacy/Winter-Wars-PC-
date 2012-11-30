#include "Snow_Factory.h"


Snow_Factory::Snow_Factory(Team *team,
			const Zeni::Point3f &position_) :
	Structure(team, position_)
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
	return "snowfactory";
}