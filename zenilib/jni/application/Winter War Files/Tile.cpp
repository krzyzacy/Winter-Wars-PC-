#include "Tile.h"
#include "Structure.h"

Tile::Tile(const Zeni::Point3f &center__,
		   const Zeni::Vector3f &scale__
		)	:
	covering(HARD_SNOW),
	Building(0)
{
	this->center = center__;
	this->size = scale__;
}


Tile::~Tile(void)
{

}

bool Tile::has_building()	{
	return !(Building == 0);
}

const model_key_t Tile::get_model_name() const	{
	switch (covering)	{
	case SOFT_SNOW:
		//return "soft_snow"
		break;
	case HARD_SNOW:
		//return "hard_snow"
		break;
	case ICE:
		//return "ICE 
		break;
	default:
		return "";
		break;
	}

}

