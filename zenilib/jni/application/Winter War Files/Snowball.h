#pragma once

#include "Moveable.h"

#include <zenilib.h>

class Collision_Table;
class Player;


class Snowball :
	public Moveable
{
public:
	Snowball(const Zeni::Point3f &center_,
              const Zeni::Vector3f &size_ = Zeni::Vector3f(10,10,10));

	~Snowball(void);
	
	void update(const float &time);

	void grow(const float &time);

	void get_thrown(const Zeni::Vector3f &dir, const float &force);

	virtual int get_ID() const 
		{return snowball_ID_c;}

	const model_key_t get_model_name() const
		{return "snowball";}

private:
	bool in_air;
	Player *owner;
	
	// Collison Stuff
	const static int snowball_ID_c;
	friend Collision_Table;
};

