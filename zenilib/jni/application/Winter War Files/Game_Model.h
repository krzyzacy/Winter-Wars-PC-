#pragma once

#include <zenilib.h>
#include <vector>

class View;
class World;
class Player;

// Remove These later!
class Permanent;

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

private:
	Game_Model(void);
	View *view;
	World *world;


	std::vector<Player*> players; 

	Permanent *Perm;
};

