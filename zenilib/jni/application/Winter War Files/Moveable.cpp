#include "Moveable.h"


Moveable::Moveable(const Zeni::Point3f &center_,
              const Zeni::Vector3f &size_ ) :
	Seen_Object(center_, size_)
{
}


Moveable::~Moveable(void)
{
}
