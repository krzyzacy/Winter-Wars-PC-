#pragma once

#include <zenilib.h>
#include <vector>
#include <String>

#include "Collision_Table.h"
#include "RakPeerInterface.h"
#include "MessageIdentifiers.h"
#include "BitStream.h"
#include "RakNetTypes.h"
#include "Utility.h"
//#include "Ingame_Client.h"
#include "Ingame_Server.h"
//#include "Ingame_Peer.h"

class Seen_Object;
class View;
class World;
class Player;
class Team;
class Moveable;
class Collidable;
class Effect;
class Structure;
class Tile;

extern const float time_to_win_c; //max time it should take to win

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
	void initialize_peer(bool isServer, RakNet::SystemAddress host_addr);
	void restart();
	void finish();

	// returns true if some team has won
	// stops the clock if yes
	bool win();

	/*set the time to win and the team to win*/
	void tree_claimed(const Team *);


	/* return time until someone wins */
	float time_till_win() const;

	/* return time game has been played*/
	float get_time() const;

	Player *get_player(int i)
		{return players.at(i);}

	Team *get_team(int i)
		{return	teams.at(i);}

	World* get_World()
		{return world;}

	Ingame_Server * get_peer()
		{return peer;}

	Tile *get_tile(const Zeni::Point3f&);

	void add_player(Player *);
	void add_moveable(Moveable *);
	void add_structure(Structure *);
	void add_effect(Effect *);

	void play_breaking();
	void play_chainbreak();
	void play_presentplace();
	void play_snowballthrow();

	/*Goes through all objects(collidables) and deletes them if they have been 
	marked fr deletion*/
	void Clean_dead();

	float get_time_step();

	void global_message(const Zeni::String &message);
	
	Collision_Table table;	

	void play_bgm();
	void stop_bgm();
private:
	
	// RakNet Peer Interface
	Ingame_Server * peer;

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

	std::set<Effect*> effects;
	

	void remove_from_model(Moveable* zombie);
	void remove_from_model(Structure* zombie);
	std::list<Moveable*> m_deletion_list;
	std::list<Structure*> s_deletion_list;
	
	void remove_from_model(Effect* zombie);
	std::list<Effect*> e_deletion_list;

	Zeni::Sound_Source * breaking;
	Zeni::Sound_Source * chainbreak;
	Zeni::Sound_Source * presentplace;
	Zeni::Sound_Source * snowballthrow;

	Zeni::Sound_Source * bgm;
};

