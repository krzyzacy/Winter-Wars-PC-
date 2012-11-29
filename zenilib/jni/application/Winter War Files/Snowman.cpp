#include "Snowman.h"


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
	return "snowman";
}