#include "Tile.h"
#include "Structure.h"

Tile::Tile(void)	:
	covering(HARD_SNOW),
	Building(0)
{
	

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

