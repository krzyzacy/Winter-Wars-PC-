#pragma once

#include "Seen_Object.h"

enum TILE_TYPE	{
	SOFT_SNOW, HARD_SNOW, ICE
};

class Structure;

class Tile :
	public Seen_Object
{
	TILE_TYPE	covering;
	Structure* Building;

public:

	bool has_building();

	Tile(void);
	~Tile(void);


};

