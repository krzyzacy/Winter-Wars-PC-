#pragma once

#include "Collidable.h"
#include "Seen_Object.h"

const float standard_speed = 100;
const Zeni::Vector3f grav_accel(0.0f, 0.0f, -9.8f);

class Moveable :
	public Collidable, public Seen_Object
{
public:
	Moveable(const Zeni::Point3f &center_,
              const Zeni::Vector3f &size_ = Zeni::Vector3f(1,1,1));
	~Moveable(void);

	void update(float time);

	void gravity(float time);


	//This will change, but simple version for now
	void set_velocity(Zeni::Vector3f vel);

	void accelerate(const Zeni::Vector3f &);

protected:
	Zeni::Vector3f velocity;
	Zeni::Vector3f accel;
};

