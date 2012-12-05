#pragma once

#include <zenilib.h>
#include <vector>
#include <String>

#include "Collision_Table.h"

class Seen_Object;
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

	// returns true if some team has won
	bool win();
	
	Player *get_player(int i)
		{return players.at(i);}

	Team *get_team(int i)
		{return	teams.at(i);}

	World* get_World()
		{return world;}

	void add_player(Player *);
	void add_moveable(Moveable *);
	void add_structure(Structure *);

	/*Goes through all objects(collidables) and deletes them if they have been 
	marked fr deletion*/
	void Clean_dead();

	float get_time_step();

	//&&&Cannot remain here
	Collision_Table table;		
private:
	Zeni::Chronometer<Zeni::Time> PlayTime;
	float time_passed;
	float time_step;
	float win_time; //set to 10000.0f to mean no one claimed tree

	Game_Model(void); //cant create any instances
	
	void check_collisions();

	View *view;
	World *world;

	std::vector<Player*>	players; 
	std::vector<Team*>		teams;

	typedef std::set<Moveable*> moveable_list_t;
	moveable_list_t movers; 
	typedef std::set<Collidable*> collidable_list_t;
	collidable_list_t colliders;
	std::set<Structure*>	structures;

	//std::set<Seen_Object*> vis_effects;
	

	void remove_from_model(Moveable* zombie);
	void remove_from_model(Structure* zombie);
	std::list<Moveable*> m_deletion_list;
	std::list<Structure*> s_deletion_list;
	

};

