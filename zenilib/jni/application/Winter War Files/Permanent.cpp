#include "Permanent.h"


Permanent::Permanent(const Zeni::Point3f &center_,
              const Zeni::Vector3f &size_,
              const Zeni::Quaternion &theta_ ) :
	Seen_Object(center_, size_, theta_)
{
}


Permanent::~Permanent(void)
{
}
