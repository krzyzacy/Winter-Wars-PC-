#pragma once

#include "Moveable.h"

class Snowball :
	public Moveable
{
public:
	Snowball(const Zeni::Point3f &center_,
              const Zeni::Vector3f &size_);

	~Snowball(void);
};

