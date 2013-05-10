#pragma once

#include "Seen_Object.h"
#include "Team.h"
#include "Structure.h"
#include <zenilib.h>

enum TILE_TYPE	{
	SOFT_SNOW, HARD_SNOW, ICE
};

//Defined in Team.h
//enum TEAM_INDEX	{
//	NEUTRAL, GREEN, RED, BLUE, ORANGE
//};

//measured from the base of the 
extern float Min_Tile_Height;
extern float Inner_Max_TH;
extern float Outer_Max_TH;

class Structure;

class Tile :
	public Seen_Object
{
	TILE_TYPE	covering;
	Structure* Building;
	TEAM_INDEX team;
	int col;
	int row;
	float tile_size;

public:

	int get_col(){ return col; }
	int get_row(){ return row; }
	float get_height() {return center.z + tile_size; }
	TEAM_INDEX get_team() {return team; }
	TILE_TYPE get_covering() {return covering; }
	Zeni::Point3f get_structure_base();


	bool set_height(float height__);
	void set_team(TEAM_INDEX teamid);
	void set_covering(TILE_TYPE coverid);
	
	//Building related
	bool has_building();
	void build_structure(Structure* buildtype, Team* new_color);
	void destroy_structure();

	Structure* get_building()	{return Building;}

	virtual const model_key_t get_model_name() const;

	//Height related stuff

	/*Note to Sen: I changed the default value of tile so I could change the size. 
		I think the world should choose the tile size though since we want to make the world
		so that no matter how large the tiles are, the world will still look correct
	*/

	Tile(const float tile_size__,
		 const Zeni::Point3f &center__ = Zeni::Point3f(0.0f,0.0f,0.0f),
		 const Zeni::Vector3f &scale__ = Zeni::Vector3f(20.0f,20.0f,20.0f),
		 const int col__ = 0,
		 const int row__ = 0
		);
	Tile(const Tile &rhs);
	Tile & operator=(const Tile &rhs);
	~Tile(void);


};

