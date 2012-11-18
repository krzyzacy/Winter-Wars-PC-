#pragma once

#include "Seen_Object.h"
#include <Zeni/Vector3f.h>

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

	Tile(const Zeni::Point3f &center__ = Zeni::Point3f(0.0f,0.0f,0.0f),
		 const Zeni::Vector3f &scale__ = Zeni::Vector3f(10.0f,10.0f,10.0f) 
		);
	~Tile(void);


};

