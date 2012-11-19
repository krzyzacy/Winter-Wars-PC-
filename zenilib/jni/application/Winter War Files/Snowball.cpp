#include "Snowball.h"

const int Snowball::snowball_ID_c = 2;

Snowball::Snowball(const Zeni::Point3f &center_,
              const Zeni::Vector3f &size_) :
	Moveable(center_, size_)
{
}


Snowball::~Snowball(void)
{
}
