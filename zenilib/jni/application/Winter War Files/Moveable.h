#pragma once

#include "Collidable.h"
#include "Seen_Object.h"

const float standard_speed = 100;
const Zeni::Vector3f grav_accel(0.0f, 0.0f, -9.8f);

class Moveable :
	public Collidable, public Seen_Object
{
protected:
	Zeni::Vector3f velocity;
	Zeni::Vector3f accel;

public:
	Moveable(const Zeni::Point3f &center_,
              const Zeni::Vector3f &size_ = Zeni::Vector3f(1,1,1));
	~Moveable(void);

	void update(const float time);

	void gravity(const float time);


	//This will change, but simple version for now
	void set_velocity(Zeni::Vector3f vel);

};

