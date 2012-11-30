#pragma once

#include <vector>

class Collidable;
class Snowball;
class Player;
class Structure;


class Collision_Table
{
public:
	Collision_Table();

	void handle_collision(int i, int j, Collidable *A, Collidable *B)
	{
		(this->*table.at(i).at(j))(A,B);
	}

	bool get_collided() { return collided;}
private:
	typedef void (Collision_Table::*fxn_ptr_t)(Collidable*, Collidable*);
	std::vector<std::vector<fxn_ptr_t> > table;

	bool collided;

	// these functions should check to see if the objects are colliding
	// and then handle the collision if they are
	void collideSnowballSnowball(Snowball*, Snowball*);
	void collidePlayerSnowball(Player*, Snowball*);
	void collideSnowballPlayer(Snowball*, Player*);
	void collidePlayerPlayer(Player*, Player*);
	void collideStructureSnowball(Structure*, Snowball*);
	void collidePlayerStructure(Player*, Structure*);
	void collideStructurePlayer(Structure*, Player*);
	void collideSnowballStructure(Snowball*, Structure*);
	void collideStructureStructure(Structure*, Structure*);
	void collideStructureG(Structure*, Collidable*);

};
