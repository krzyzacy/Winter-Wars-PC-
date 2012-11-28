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

void Tile::set_team(TEAM_INDEX teamid){
	team = teamid;
}
void Tile::set_covering(TILE_TYPE coverid){
	covering = coverid;
}

const model_key_t Tile::get_model_name() const	{

	switch (team){
		case NEUTRAL:
			switch (covering){
				case SOFT_SNOW:
					return "neutralsoftsnowtile";
					break;
				case HARD_SNOW:
					return "neutralhardsnowtile";
					break;
				case ICE:
					return "neutralicetile";
					break;
				default:
					return "";
					break;
			}
		break;
			break;
		case GREEN:
			switch (covering){
				case SOFT_SNOW:
					return "greensoftsnowtile";
					break;
				case HARD_SNOW:
					return "greenhardsnowtile";
					break;
				case ICE:
					return "greenicetile";
					break;
				default:
					return "";
					break;
			}
			break;
		case RED:
			switch (covering){
				case SOFT_SNOW:
					return "redsoftsnowtile";
					break;
				case HARD_SNOW:
					return "redhardsnowtile";
					break;
				case ICE:
					return "redicetile";
					break;
				default:
					return "";
					break;
			}
			break;
		case BLUE:
			switch (covering){
				case SOFT_SNOW:
					return "bluesoftsnowtile";
					break;
				case HARD_SNOW:
					return "bluehardsnowtile";
					break;
				case ICE:
					return "blueicetile";
					break;
				default:
					return "";
					break;
			}
			break;
		case ORANGE:
			switch (covering){
				case SOFT_SNOW:
					return "orangesoftsnowtile";
					break;
				case HARD_SNOW:
					return "orangehardsnowtile";
					break;
				case ICE:
					return "orangeicetile";
					break;
				default:
					return "";
					break;
			}
			break;
		default:
			return "";
			break;
	}



}

