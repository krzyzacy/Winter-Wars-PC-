#pragma once

#include <vector>
#include "View.h"
#include "Tile.h"

using namespace std;

class World
{
public:
	World( const int width__ = 15,
		   const int height__ = 14,
		   const float hex_length__ = 50.0f
		);
	~World(void);

	Tile * get_tile(const Zeni::Point3f &position);

	// view or model?

private:

	vector< vector<Tile *> > map;

	int map_width;                   // number of tiles in a row
	int map_height;                  // number of tiles in a column
	float tile_size;                   // size of a tile
	
		
};

