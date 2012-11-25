#pragma once

#include <zenilib.h>

class World;
class Tile;
class Player;
class Base;

class Team
{	
public:
	Team(void); //Enter Players, And Color?
	~Team(void);

	
	bool Is_Tree_Claimed();
	void Start_Victory_Countdown();
	bool Hail_to_the_Victors();	//Tells the rest of the game we've won

	void update(float time);
	void check_connectivity();	//Deactivates tiles if they aren't connected
	void add_tile(Tile *);
	void remove_tile(Tile *);


private:
	//list of players
	std::list<Player*>	members;
	//Resource value
	float Ice_Blocks;
	float intake_rate;

	//Class network (new Class)
	World*	Land;

	std::set<Tile*>	Newtwork;
	std::set<Tile*> Adjacent_Tiles;
		//Holds tile information pertininet to team
	std::set<Tile*> Disconnected_Tiles;

	Base* Home;




};

