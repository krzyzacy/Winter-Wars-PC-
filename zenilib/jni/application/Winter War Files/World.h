#pragma once

#include <vector>

#include <zenilib.h>
#include <list>

class View;
class Tile;

extern const float Ice_friction;
extern const float Norml_friction;
extern float Tile_Move_Speed;

class World
{
public:
	World( View *view_,
		   const int width__ = 14,
		   const int height__ = 13,
		   const float hex_length__ = 100.0f
		);
	~World(void);

	Tile * get_tile(const Zeni::Point3f &position);
	Tile * get_tile(int row, int col);
	int get_width(){return map_width; };
	int get_height(){return map_height; };

	Tile * player_is_looking_at(const Zeni::Point3f &player_pos, Zeni::Vector3f look_dir);

	//change input type if you want, or make multiple types
	bool is_adjacent(Tile* A, Tile* B);
	bool is_boundary_tile(Tile *t);

	void raise_tile(Zeni::Point3f location);
	void raise_tile(Tile* ti);
	void lower_tile(Zeni::Point3f location);
	void lower_tile(Tile* ti);

	float get_friction_coeff(Zeni::Point3f &spot);
	bool allowed_to_scoop(Zeni::Point3f &pos_);

	bool Sine_Wave_is_Active()	{return sine_active;}
	void Run_Sine_Wave();
	void Activate_Sine_Wave();
	
	/*Returns the six adjacent tiles to Central*/
	std::list<Tile*> Get_Family(Tile *Central);
	// view or model?

	//Called during set up, gives next Tile that represents the base
	Tile* get_next_Base_Tile();
	Tile* get_center_Tile() {return map[6][7]; };
	
	/* returns height of ground at that location*/
	float get_ground_height(Zeni::Point3f location);

private:

	std::vector< std::vector<Tile *> > map;
	View *view;
	int map_width;                   // #col
	int map_height;                  // #row
	float tile_size;                 // size of a tile
	int cur_team_count;
	
	//Sin wave stuff
	bool sine_active;
	bool crest_past_start; //true only after the crest of the wave has moved pass the start
	int sine_ticks;
	int wave_row;
	std::set<Tile*> ascending;
	std::set<Tile*> descending;



};
