#pragma once

#include <zenilib.h>

class World;
class Tile;
class Player;

enum TEAM_INDEX	{
	NEUTRAL, GREEN, RED, BLUE, ORANGE
};



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
	void add_tile(Tile *);
	void remove_tile(Tile *);

	bool is_in_network(Tile *);
	bool is_adjacent_to_network(Tile *);

	//Building related
	bool tile_is_ready(Tile * candidate, int type);

	//Set Up and utility
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

	struct Stats{
		Stats() :
			total_resources(0), largest_network(0), 
			tiles_lost(0), final_network(0), resources_spent(0)
		{
			for (int i = 0 ; i < 5 ; i++)
				structures[i] = 0;
		}
		int total_resources;
		int largest_network;
		int tiles_lost;
		int final_network;	
		int resources_spent;
		int structures[5];
	
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


};

