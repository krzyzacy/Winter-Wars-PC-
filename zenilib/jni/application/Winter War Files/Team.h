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
	bool Hail_to_the_Victors();	//Tells the rest of the game we've won

	//Network related
	void update();
	void check_connectivity();	//Deactivates tiles if they aren't connected
	void add_tile(Tile *);
	void remove_tile(Tile *);

	bool is_in_network(Tile *);
	bool is_adjacent_to_network(Tile *);

	//Set Up and utility
	int get_Resources()	const {return Ice_Blocks;}
	void set_Team_Color(TEAM_INDEX in);
	TEAM_INDEX get_Team_Index()	{return Team_Color;}

private:
	//list of players
	std::vector<Player*>	members;
	//Resource value
	int Ice_Blocks;
	int intake_rate;
	Zeni::Chronometer<Zeni::Time> ResourceTime;

	TEAM_INDEX	Team_Color;

	
	std::set<Tile*>	Network;
	std::set<Tile*> Adjacent_Tiles;
		//Holds tile information pertininet to team
	std::set<Tile*> Disconnected_Tiles;

	Tile* Base;




};

