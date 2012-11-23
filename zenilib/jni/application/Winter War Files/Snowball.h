#pragma once

#include "Moveable.h"

class Collision_Table;
class Player;


class Snowball :
	public Moveable
{
public:
	Snowball(const Zeni::Point3f &center_,
              const Zeni::Vector3f &size_);

	~Snowball(void);
	
	void update(float time);
	void render() const;

	void get_thrown(const Zeni::Vector3f &dir);

	virtual int get_ID() const 
		{return snowball_ID_c;}

private:
	bool in_air;
	Player *owner;
	
	// Collison Stuff
	const static int snowball_ID_c;
	friend Collision_Table;
};

