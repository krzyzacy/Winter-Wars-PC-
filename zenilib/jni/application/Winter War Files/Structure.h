#pragma once
#include "Collidable.h"
#include "Seen_Object.h"

#include <zenilib.h>

//These enums represnt the different types of buildings for now
//Will eventually be able to plug these into create_structure
//From object factory, hopefully anyway

// THIS IS AWFUL!!!!!!!!!
// Delete this now!!!! USe the object factory to create it.  Minimize work in player.cpp
enum Structure_Type	{
	NOTHING, SNOWMAN, FORT, SNOW_FACTORY, HEALING_POOL
};


class Team;
class Collision_Table;

class Structure :
	public Collidable, public Seen_Object
{
public:
	Structure(Team *team,
			const Zeni::Point3f &position_,
			float radius_from_tile_center = 10.0f
            );
	~Structure(void);

	void update(const float&);

private:
	// Stuff every structure needs... 
	
	// State?  Building -> Built -> Damaged? -> Destroyed??
	
	// Health?

	// maybe Collision capsule??? If each structure needs Collision Object, 
	// Collision table becomes much more complicated to code
	// But some effects might need players to run into them
	// Solution: make defualt body, but can overwrite in derived classes if need to

	Team *owner;

	// Maybe Tile?

	
	void create_body();
		
	// Collison Stuff
	const static int structure_ID_c;
	friend Collision_Table;

};

