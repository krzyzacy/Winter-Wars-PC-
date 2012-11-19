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

	void collideSnowballSnowball(Snowball*, Snowball*);
	void collidePlayerSnowball(Player*, Snowball*);
	void collideSnowballPlayer(Snowball*, Player*);
	void collidePlayerPlayer(Player*, Player*);
	void collidePermanentSnowball(Permanent*, Snowball*);
	void collidePlayerPermanent(Player*, Permanent*);
	void collidePermanentPlayer(Permanent*, Player*);
	void collideSnowballPermanent(Snowball*, Permanent*);
	void collidePermanentPermanent(Permanent*, Permanent*);
	void collidePermanentG(Permanent*, Collidable*);


};
