#pragma once

#include <vector>

class Collidable;
class Snowball;
class Player;
class Permanent;


class Collision_Table
{
public:
	Collision_Table();

	void handle_collision(int i, int j, Collidable *A, Collidable *B)
	{
		(this->*table.at(i).at(j))(A,B);
	}

private:
	typedef void (Collision_Table::*fxn_ptr_t)(Collidable*, Collidable*);
	std::vector<std::vector<fxn_ptr_t> > table;

	void collideBB(Snowball*, Snowball*);
	void collidePB(Player*, Snowball*);
	void collideBP(Snowball*, Player*);
	void collidePP(Player*, Player*);
	void collideWB(Permanent*, Snowball*);
	void collidePW(Player*, Permanent*);
	void collideWP(Permanent*, Player*);
	void collideBW(Snowball*, Permanent*);
	void collideWW(Permanent*, Permanent*);
	void collideWG(Permanent*, Collidable*);


};
