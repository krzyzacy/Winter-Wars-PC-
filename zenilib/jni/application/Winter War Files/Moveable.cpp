#include "Moveable.h"

using namespace std;
using namespace Zeni;


Moveable::Moveable(const Zeni::Point3f &center_,
              const Zeni::Vector3f &size_ ) :
	Seen_Object(center_, size_)
{
}


Moveable::~Moveable(void)
{
}

void Moveable::gravity(float time)	{
	if(!is_on_ground())	
		velocity += grav_accel * time * time;
}

void Moveable::update(float time)	{
	center += velocity * time;
	
}

void Moveable::set_velocity(const Vector3f vel)	{
	velocity = vel;
}

void Moveable::accelerate(const Vector3f &acc)
{
	accel += acc;
}
