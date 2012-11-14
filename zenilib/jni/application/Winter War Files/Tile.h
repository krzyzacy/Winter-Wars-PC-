#pragma once
<<<<<<< HEAD
#include "Renderable.h"

enum TILE_TYPE	{
	SOFT_SNOW, HARD_SNOW, ICE
};

class Structure;

=======
#include "Seen_Object.h"
>>>>>>> ec6699d60743b9ffb5cc513d362d3e4a4073be77
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

