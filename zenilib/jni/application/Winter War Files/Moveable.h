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

	virtual Zeni::Vector3f get_velocity()	{return velocity;}

	virtual void network_overwrite_members(Zeni::Point3f &pos, Zeni::Vector3f &vel);

protected:
	Zeni::Vector3f velocity;	
	
	// template functions that happen during update
	// derived classes define 
	virtual void off_map() = 0;
	virtual void hit_tile() = 0;
	virtual void on_ground() = 0;

};