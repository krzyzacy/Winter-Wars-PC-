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

class Level;

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
	void change_level(Level *new_level);
	void start_up(const std::vector<Player_info*> &player_info);
	void stop();
	void initialize_peer(bool isServer, RakNet::SystemAddress host_addr);
	void restart();
	void clean();

	std::string get_level_name();
	int get_game_id();

	// returns true if some team has won
	// stops the clock if yes
	bool win();

	// returns winning team if there is one
	Team *get_winning_team();

	/*set the time to win and the team to win*/
	void tree_claimed(const Team *);

	/* return time until someone wins */
	float time_till_win() const;

	/* return time game has been played*/
	float get_time() const;

	Player *get_player(int i);

	int num_players();

	/* returns the ith player on this machine*/
	Player *get_player_here(int index_on_this_client);
	int num_players_here();

	Team *get_team(int i);

	World* get_World();

	Ingame_Server * get_peer();

	Tile *get_tile(const Zeni::Point3f&);
	Tile *get_tile(int row, int col);
	Tile *get_center_tile();

	void add_moveable(Moveable *);
	void add_structure(Structure *);
	void add_effect(Effect *);
	void add_player(Player *);

	void play_breaking();
	void play_chainbreak();
	void play_presentplace();
	void play_snowballthrow();

	/*Goes through all objects(collidables) and deletes them if they have been 
	marked fr deletion*/
	void Clean_dead();

	float get_time_step();
	float get_time_passed();
	float get_time_left();

	void global_message(const Zeni::String &message);

	Collision_Table table;	

	void play_bgm();
	void stop_bgm();
private:
	Game_Model(void); //cant create any instances
	
	Zeni::Sound_Source * breaking;
	Zeni::Sound_Source * chainbreak;
	Zeni::Sound_Source * presentplace;
	Zeni::Sound_Source * snowballthrow;

	Zeni::Sound_Source * bgm;

	Level *current_level;
	int id;

};
