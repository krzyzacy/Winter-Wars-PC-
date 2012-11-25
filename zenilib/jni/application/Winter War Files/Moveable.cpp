#include "Moveable.h"

using namespace std;
using namespace Zeni;


const Zeni::Vector3f grav_accel(0.0f, 0.0f, -9.8f);

Moveable::Moveable(const Point3f &center_, const Vector3f &size_ ) :
	Seen_Object(center_, size_)
	, velocity(Vector3f())
	, accel(Vector3f())
{
}


Moveable::~Moveable(void)
{
}

void Moveable::gravity()	{
	if(!is_on_ground())
		accel += grav_accel;
	else
		accel = Vector3f();
}

void Moveable::update(const float &time)	{
	
	// gravity(time);

	velocity += accel * time;
	center += velocity * time;

	if(is_on_ground() && accel.z != 0)	{
		accel = Vector3f();
		velocity = Vector3f();
	}

	// reset accel
	// This gives everything acceleration pulses.
	//accel = Vector3f();
}

void Moveable::set_velocity(const Vector3f vel)	{
	velocity = vel;
}

void Moveable::accelerate(const Vector3f &acc)
{
	accel += acc;
}
