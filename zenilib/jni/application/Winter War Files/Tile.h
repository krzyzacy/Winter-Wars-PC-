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
	int col;
	int row;

public:

	int get_col(){ return col; }
	int get_row(){ return row; }

	bool has_building();

	virtual const model_key_t get_model_name() const;

	//Height related stuff

	/*Note to Sen: I changed the default value of tile so I could change the size. 
		I think the world should choose the tile size though since we want to make the world
		so that no matter how large the tiles are, the world will still look correct
	*/

	Tile(const Zeni::Point3f &center__ = Zeni::Point3f(0.0f,0.0f,0.0f),
		 const Zeni::Vector3f &scale__ = Zeni::Vector3f(20.0f,20.0f,2.0f),
		 const int col__ = 0,
		 const int row__ = 0
		);
	~Tile(void);


};

