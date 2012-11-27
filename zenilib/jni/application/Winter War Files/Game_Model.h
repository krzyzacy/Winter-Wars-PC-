#pragma once

#include <zenilib.h>
#include <vector>

#include "Collision_Table.h"

class View;
class World;
class Player;
class Moveable;
class Collidable;
class Snowball;

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
	void start_up();
	
	Player *get_player(int i)
		{return players.at(i);}

	void add_moveable(Moveable *);

	void remove_moveable(Moveable *);

	/*Goes through Moveables and removes "dead" ones*/
	void Clean_Moving_dead();

	float get_time_step();

	Collision_Table table;		
private:
	Zeni::Chronometer<Zeni::Time> PlayTime;
	float time_passed;
	float time_step;

	Game_Model(void);
	View *view;
	World *world;

	std::vector<Player*> players; 

	typedef std::set<Moveable*> moveable_list_t;
	moveable_list_t movers; 
	
	typedef std::set<Collidable*> collidable_list_t;
	collidable_list_t colliders;
	
	// Functions
	void check_collisions();

};

