#pragma once

#include <zenilib.h>
#include "Stats.h"

class World;
class Tile;
class Player;
class Structure;

extern float Max_Resources;
extern float starting_resources;
extern float hard_snow_intake;
extern float soft_snow_intake;
extern float ice_intake;

class Team
{	
public:
	Team(Tile* BaseTile = 0); //Enter Players, And Color?
	~Team(void);

	void add_player(Player *);
	
	//Victory Stuf
	bool Is_Tree_Claimed();
	void Start_Victory_Countdown();
	void Stop_Victory_Countdown();
	bool win();	//Tells the rest of the game we've won
	float time_till_win();

	//Network related
	void update();
	void check_connectivity();	//Deactivates tiles if they aren't connected
	void Deactivate_disconnected();
	void reintegrate_connected();
	
	void remove_tile(Tile *);

	bool is_in_network(Tile *);
	bool is_adjacent_to_network(Tile *);
	void destabilize_network()	{network_unstable = true;}
	void modify_resources(int amt);
	int take_resources(int amt);

	void message_team(const Zeni::String &message, int priority = 0);

	bool is_empty(){ return members.size() == 0; }

	//Building related
	bool allowed_to_build_on_Tile(Tile* candidate);
	bool can_afford_building(int type);
	void add_tile_to_team_network(Tile* new_tile);
	void pay_for_building(Structure *);



	//Set Up and utility
	int get_Player_Kills();
	int get_Resources()	const {return Ice_Blocks;}
	void set_Team_Color(TEAM_INDEX in);
	TEAM_INDEX get_Team_Index()	{return Team_Color;}
	Zeni::Point3f get_spawn_point() const;

	// returns null if index == number of players
	Player *get_player(int index);

	 // returns "orange", "blue", etc.
	Zeni::String get_name();

	// returns "Orange", "Blue"
	Zeni::String get_name_Upper_Case();

	struct Team_Stats: public Stats{
		Team_Stats();
		//int total_kills;
		int total_resources;
		int largest_network;
		int tiles_lost;
		int final_network;	
		int resources_spent;
		int structures[10];
	
		int all_structures()
		{	int ret = 0;
			for (int i = 0 ; i < 5 ; i++)
				ret += structures[i];
			return ret;
		}

	} stats;

private:
	//list of players
	std::vector<Player*>	members;
	bool network_unstable;

	//Resource value
	int Ice_Blocks;
	int intake_rate;

	Zeni::Chronometer<Zeni::Time> ResourceTime;
	Zeni::Chronometer<Zeni::Time> WinTimer;

	TEAM_INDEX	Team_Color;

	//Holds tile information pertininet to team
	std::set<Tile*>	Network;
	std::set<Tile*> Adjacent_Tiles;
	std::set<Tile*> Disconnected_Tiles;

	Tile* Base;

	void add_tile(Tile *);

};

