#pragma once
#include "Collidable.h"
#include "Seen_Object.h"

#include <zenilib.h>

//These enums represnt the different types of buildings for now
//Will eventually be able to plug these into create_structure
//From object factory, hopefully anyway

// THIS IS AWFUL!!!!!!!!!
// Delete this now!!!! USe the object factory to create it.  Minimize work in player.cpp

//This works though. 
//	I know it's sinful, but it will suffice for now. Besides I don't see a way around it with what I need it to do
//	at least for now, probably one will become clear soon enough.
enum Structure_Type	{
	NOTHING, SNOWMAN, FORT, SNOW_FACTORY, HEALING_POOL
};


enum	Universal_State	{
	PRESENT_MODE, BUILT, DAMAGED, DESTROYED
};

class Team;
class Collision_Table;

class Structure :
	public Collidable, public Seen_Object
{
public:
	Structure(Team *team,
			const Zeni::Point3f &position_,
			float radius_from_tile_center = 100.0f
            );
	~Structure(void);

	void update(const float&);

	int get_ID() const 
		{return structure_ID_c;}

private:
	// Stuff every structure needs... 
	
	// State?  Building -> Built -> Damaged? -> Destroyed??
	//Would the damaged state look different? like a broken version of the model???
	//could be cool
	
protected:
	float Health;
	Universal_State Status;
	bool Connected_to_Team;

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

