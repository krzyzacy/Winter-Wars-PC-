#pragma once

#include "Moveable.h"

class Collision_Table;

class Snowball :
	public Moveable
{
public:
	Snowball(const Zeni::Point3f &center_,
              const Zeni::Vector3f &size_);

	~Snowball(void);
	
	virtual int get_ID() const 
		{return snowball_ID_c;}

private:

	
	// Collison Stuff
	const static int snowball_ID_c;
	friend Collision_Table;
};

