#pragma once

#include <zenilib.h>
#include <vector>
#include <String>

#include "Collision_Table.h"

class View;
class World;
class Player;
class Team;
class Moveable;
class Collidable;
class Structure;


class Game_Model
{
public:
	static Game_Model &get()
	{
		static Game_Model m;
		return m;
	}
	
	~Game_Model(void);

	void update();
	void render() const;
	void start_up(const std::vector<Zeni::String> &genders_, const std::vector<int> &colors_);
	void finish();
	
	Player *get_player(int i)
		{return players.at(i);}

	Team *get_team(int i)
		{return	teams.at(i);}

	World* get_World()
		{return world;}

	void add_player(Player *);

	void add_moveable(Moveable *);
	void remove_moveable(Moveable *);

	void add_structure(Structure *);
	void remove_structure(Structure *);

	/*Goes through Moveables and removes "dead" ones*/
	void Clean_Moving_dead();

	/*When an object has determined it's time to die, call this function
	Is not meant for players*/
	void Kill_me(Snowball *);
	void Kill_me(Structure *);

	float get_time_step();

	//&&&Cannot remain here
	Collision_Table table;		
private:
	Zeni::Chronometer<Zeni::Time> PlayTime;
	float time_passed;
	float time_step;

	Game_Model(void); //cant create any instances

	View *view;
	World *world;

	std::vector<Player*>	players; 
	std::vector<Team*>		teams;

	typedef std::set<Moveable*> moveable_list_t;
	moveable_list_t movers; 
	
	typedef std::set<Collidable*> collidable_list_t;
	collidable_list_t colliders;

	std::set<Structure*>	structures;
	
	// Functions
	void check_collisions();

};

