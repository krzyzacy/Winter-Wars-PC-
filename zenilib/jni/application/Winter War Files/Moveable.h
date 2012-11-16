#pragma once

#include "Collidable.h"
#include "Seen_Object.h"

class Moveable :
	public Collidable, public Seen_Object
{
public:
	Moveable(void);
	~Moveable(void);
};

