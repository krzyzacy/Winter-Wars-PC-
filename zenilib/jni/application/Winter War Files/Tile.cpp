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

