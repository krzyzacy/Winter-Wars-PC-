#include "Tile.h"
#include "Structure.h"

Tile::Tile(const Zeni::Point3f &center__,
		   const Zeni::Vector3f &scale__,
		   const int col__,
		   const int row__
		)	:
	covering(HARD_SNOW),
	Building(0)
{
	this->center = center__;
	this->size = scale__;
	this->col = col__;
	this->row = row__;
}

Tile::Tile(const Tile &rhs
		)	:
	covering(rhs.covering),
	Building(rhs.Building)
{
	this->center = rhs.center;
	this->size = rhs.size;
	this->col = rhs.col;
	this->row = rhs.row;
}

Tile & Tile::operator=(const Tile &rhs
		)
{
	this->covering = rhs.covering;
	this->Building = rhs.Building;
	this->center = rhs.center;
	this->size = rhs.size;
	this->col = rhs.col;
	this->row = rhs.row;

	return *this;
}


Tile::~Tile(void)
{

}

bool Tile::has_building()	{
	return !(Building == 0);
}

const model_key_t Tile::get_model_name() const	{

	return "simpletile";

	/*

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

	*/

}

