#include "Tile.h"
#include "Structure.h"
#include "Object_factory.h"
#include "Team.h"
#include "Game_Model.h"

using namespace Zeni;
using namespace std;

const float Max_Tile_Height = 250;
const float Min_Tile_Height = 100;


Tile::Tile(const float tile_size__,
		   const Zeni::Point3f &center__,
		   const Zeni::Vector3f &scale__,
		   const int col__,
		   const int row__
		)	:
	covering(HARD_SNOW),
	Building(0)
{
	this->tile_size = tile_size__;
	this->center = center__;
	this->size = scale__;
	this->col = col__;
	this->row = row__;
}

Tile::Tile(const Tile &rhs
		)	:
	covering(rhs.covering),
	Building(rhs.Building),
	tile_size(rhs.tile_size)
{
	this->center = rhs.center;
	this->size = rhs.size;
	this->col = rhs.col;
	this->row = rhs.row;
}

Tile & Tile::operator=(const Tile &rhs
		)
{
	this->tile_size = rhs.tile_size;
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

bool Tile::set_height(float height__){
	if((get_height() == Max_Tile_Height && height__ > 0) 
		|| (get_height() == Min_Tile_Height && height__ < 0))
		return false;

	center.z += height__;
	if(has_building())	
		Building->change_height(height__);
	
	if(get_height() > Max_Tile_Height)	{
		if(has_building()) Building->change_height(-abs(get_height() - Max_Tile_Height));
		center.z = Max_Tile_Height - tile_size;
	}
	if(get_height() < Min_Tile_Height)	{
		if(has_building()) Building->change_height(abs(Min_Tile_Height - get_height()));
		center.z = Min_Tile_Height - tile_size;
	}
	
	return true;
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

Point3f Tile::get_structure_base()	{
	return Point3f(center.x, center.y, get_height());
}

void Tile::build_structure(Structure* S, Team* new_team)	{
	if(new_team)
		team = new_team->get_Team_Index();
	Building = S;
}

void Tile::destroy_structure()	{
	//Will add more here later, but tile should be interface for interacting with a structure
	Structure* S = Building;
	Building = 0;
	Game_Model::get().remove_structure(S);
}

