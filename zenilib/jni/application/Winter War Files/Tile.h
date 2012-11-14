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

	virtual const model_key_t get_model_name() const;

	Tile(void);
	~Tile(void);


};

