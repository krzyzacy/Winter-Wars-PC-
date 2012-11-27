#include "Moveable.h"

using namespace std;
using namespace Zeni;


const Zeni::Vector3f grav_accel(0.0f, 0.0f, -125.0f);

Moveable::Moveable(const Point3f &center_, const Vector3f &size_ ) :
	Seen_Object(center_, size_)
	, velocity(Vector3f())
{
}


Moveable::~Moveable(void)
{
}

void Moveable::gravity(const float &time)	{
	if(!is_on_ground())
		velocity += grav_accel * time;
	else if(velocity.z < 0)
		velocity.z = 0;
}

void Moveable::update(const float &time)	{
	Collidable::update(time);

	gravity(time);
	center += velocity * time;
}

void Moveable::set_velocity(const Vector3f &vel)	{
	velocity = vel;
}

void Moveable::accelerate(const Vector3f &acc, const float &time)	{
	velocity += acc * time;
}

/*
	//if(is_on_ground())
	//	velocity += Vector3f(0,0,50);
	
	accelerate(jump_vec,time);
	

const Vector3f jump_vec(0,0,400);

*/

