#pragma once

#include <vector>

#include <zenilib.h>
#include <list>

class View;
class Tile;


class World
{
public:
	World( View *view_,
		   const int width__ = 15,
		   const int height__ = 14,
		   const float hex_length__ = 100.0f
		);
	~World(void);

	Tile * get_tile(const Zeni::Point3f &position);

	Tile * player_is_looking_at(Zeni::Point3f &player_pos, Zeni::Vector3f look_dir);

	//change input type if you want, or make multiple types
	bool is_adjacent(Tile* A, Tile* B);

	//Boundary check?
	
	/*Returns the six adjacent tiles to Central*/
	std::list<Tile*> Get_Family(Tile *Central);
	// view or model?

	//Called during set up, gives next Tile that represents the base
	Tile* get_next_Base_Tile();


private:

	std::vector< std::vector<Tile *> > map;
	View *view;
	int map_width;                   // number of tiles in a row
	int map_height;                  // number of tiles in a column
	float tile_size;                 // size of a tile
	
		
};
