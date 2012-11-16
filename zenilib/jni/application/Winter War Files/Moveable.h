#pragma once

#include "Collidable.h"
#include "Seen_Object.h"

class Moveable :
	public Collidable, public Seen_Object
{
public:
	Moveable(const Zeni::Point3f &center_,
              const Zeni::Vector3f &size_ = Zeni::Vector3f(1,1,1));
	~Moveable(void);
};

