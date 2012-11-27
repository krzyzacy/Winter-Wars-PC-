#pragma once

#include "Collidable.h"
#include "Seen_Object.h"

// moved consts to cpp file to keep them local to moveable,
//  no reason to include them everywhere

class Moveable :
	public Collidable, public Seen_Object
{
public:
	Moveable(const Zeni::Point3f &center_,
              const Zeni::Vector3f &size_ = Zeni::Vector3f(1,1,1));
	~Moveable(void);

	virtual void update(const float &time) = 0;

	void gravity(const float &time);


	//This will change, but simple version for now
	void set_velocity(const Zeni::Vector3f &vel);

	void accelerate(const Zeni::Vector3f &, const float &time);

protected:
	Zeni::Vector3f velocity;
	


	//Zeni::Vector3f accel;
};