#pragma once
#include "Collidable.h"
#include "Seen_Object.h"
#include "StructureAnimator.h"
#include "StructureAnimators.h"

#include <zenilib.h>

enum Structure_Type	{
	NOTHING, SNOWMAN, FORT, SNOW_FACTORY, HEALING_POOL, TREE, BASE
};

//These enums represnt the different types of buildings for now

extern float Build_Cost[5];

extern float Struct_Integrity[5];

enum	Universal_State	{
	PRESENT_MODE, UNWRAP_MODE, BUILT, DAMAGED, DESTROYED
};

class Team;
class Collision_Table;
class Tile;
class Snowball;
class Player;
class StructureAnimator;
enum StructureEvent_e;

class Structure :
	public Collidable, public Seen_Object
{
public:
	Structure(Team *team, Tile* tile_,
				const Zeni::Point3f &base_,	 float radius = 100.0f);
	~Structure(void);

	void update(const float&);

	virtual Structure_Type get_type() = 0;

	void change_height(const float &delta);

	void receive_hit(float damage); 

	virtual void handle_player_collision(Player *P);
	virtual void destabilize_network()	{}
	Team* get_team_pt()	{return owner;}

	void perform_destruction_effects();

	void begin_isolation();
	void reintegrate();

	virtual void handle_player_in_range(Team* color, Zeni::Collision::Capsule &person)	{}
	
	int get_ID() const 
		{return structure_ID_c;}

	virtual bool is_snow_maker()	{return false;}

	void save_position();

private:
	// State?  Building -> Built -> Damaged? -> Destroyed??
	//Would the damaged state look different? like a broken version of the model???
	//could be cool
	
protected:
	float Health;
	Universal_State Status;
	bool Connected_to_Team;

	Zeni::Point3f default_position;
	Zeni::Vector3f default_size;
	float default_radius;
	// maybe Collision capsule??? If each structure needs Collision Object, 
	// Collision table becomes much more complicated to code
	// But some effects might need players to run into them
	// Solution: make defualt body, but can overwrite in derived classes if need to

	Team *owner;

	Tile *hex;

	Zeni::Chronometer<Zeni::Time> Isolation_Clock;
	//Present Stuff
	Zeni::Chronometer<Zeni::Time> Present_Clock;	
	bool opened;

	void create_body();
	Zeni::Collision::Capsule body;
		
	// Collison Stuff
	const static int structure_ID_c;
	friend Collision_Table;

	// Animation
	StructureAnimator *animation_state;
	virtual Animator *get_animator() const;
	virtual void switch_state(StructureEvent_e);

	void restore_default_size_and_position();
	float save_height;
};

