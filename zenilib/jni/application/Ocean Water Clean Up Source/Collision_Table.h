#pragma once

#include <vector>

class Game_Object;
class Snowball;
class Player;
class Target;


class Collision_Table
{
public:
	Collision_Table();

	void handle_collision(int i, int j, Game_Object *A, Game_Object *B)
	{
		(this->*table.at(i).at(j))(A,B);
	}

private:
	typedef void (Collision_Table::*fxn_ptr_t)(Game_Object*, Game_Object*);
	std::vector<std::vector<fxn_ptr_t> > table;

	void collideBB(Snowball*, Snowball*);
	void collidePB(Player*, Snowball*);
	void collideBP(Snowball*, Player*);
	void collidePP(Player*, Player*);
	void collideWB(Target*, Snowball*);
	void collidePW(Player*, Target*);
	void collideWP(Target*, Player*);
	void collideBW(Snowball*, Target*);
	void collideWW(Target*, Target*);
	void collideWG(Target*, Game_Object*);


};
