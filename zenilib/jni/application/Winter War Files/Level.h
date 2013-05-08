
#ifndef LEVEL_H
#define LEVEL_H

#include <zenilib.h>
#include <vector>
#include <String>

#include "Collision_Table.h"
#include "RakPeerInterface.h"
#include "MessageIdentifiers.h"
#include "BitStream.h"
#include "RakNetTypes.h"
#include "Utility.h"
#include "Ingame_Server.h"

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

class Level
{
public:
	Level();
	virtual ~Level();

	virtual void update();
	virtual void render() const;
	virtual void start_up(const std::vector<Player_info*> &player_info);
	virtual void stop();
	virtual void initialize_peer(bool isServer, RakNet::SystemAddress host_addr);
	virtual void restart();
	virtual void clean();

	// returns true if some team has won
	// stops the clock if yes
	virtual bool win() = 0;

	virtual Team* get_winning_team() { return winning_team; }
	virtual void set_winning_team(Team* winning_team_) { winning_team = winning_team_; }

	/*set the time to win and the team to win*/
	virtual void tree_claimed(const Team *);

	/* return time until someone wins */
	virtual float time_till_win() const;

	/* return time game has been played*/
	virtual float get_time() const;

	Player *get_player(int i)
		{return players.at(i);}

	int num_players() {return players.size();}

	/* returns the ith player on this machine*/
	Player *get_player_here(int index_on_this_client);
	
	int num_players_here();

	Team *get_team(int i)
		{return	teams.at(i);}

	World* get_World()
	{return world;}

	Ingame_Server * get_peer()
		{return peer;}

	Tile *get_tile(const Zeni::Point3f&);
	Tile *get_tile(int row, int col);
	virtual Tile *get_center_tile();

	void add_player(Player *);
	void add_moveable(Moveable *);
	void add_structure(Structure *);
	void add_effect(Effect *);
	
	/*Goes through all objects(collidables) and deletes them if they have been 
	marked fr deletion*/
	void Clean_dead();

	float get_time_step();

	void global_message(const Zeni::String &message);

	Collision_Table table;	

protected:
	Zeni::Chronometer<Zeni::Time> PlayTime;

private:

	// RakNet Peer Interface
	Ingame_Server * peer;

	float time_passed;
	float time_step;

	float win_time; //set to 10000.0f to mean no one claimed tree
	
	void check_collisions();

	View *view;
	World *world;

	std::vector<Player*>	players; 
	std::vector<Team*>		teams;

	Team* winning_team;

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


	std::vector<Player_info*> init_player_info;
	std::map<RakNet::SystemAddress, std::vector<Player *> > clients_to_players;


};

#endif 