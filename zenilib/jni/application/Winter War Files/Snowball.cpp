#include "Snowball.h"

#include <zenilib.h>

const int Snowball::snowball_ID_c = 2;

using namespace Zeni;

Snowball::Snowball(const Zeni::Point3f &center_,
              const Zeni::Vector3f &size_) :
	Moveable(center_, size_)	
	, in_air(false)
//	, owner(p)
{
}


Snowball::~Snowball(void)
{
}

void Snowball::update(const float &time)
{	
	if (in_air)
	{
		Moveable::update(time);
	}
	else
	{
	
	}
}

void Snowball::get_thrown(const Vector3f &dir, const float &force)
{
	in_air = true;

	accelerate(dir*force);
}
