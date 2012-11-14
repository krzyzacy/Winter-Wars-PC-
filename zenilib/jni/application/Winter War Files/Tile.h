#pragma once
#include "Renderable.h"

enum TILE_TYPE	{
	SOFT_SNOW, HARD_SNOW, ICE
};

class Structure;

class Tile :
	public Renderable
{
	TILE_TYPE	covering;
	Structure* Building;

public:

	bool has_building();

	Tile(void);
	~Tile(void);




};

