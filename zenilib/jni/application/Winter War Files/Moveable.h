#pragma once

#include "Collidable.h"

class Moveable :
	public Collidable, public Seen_Object
{
public:
	Moveable(void);
	~Moveable(void);
};

