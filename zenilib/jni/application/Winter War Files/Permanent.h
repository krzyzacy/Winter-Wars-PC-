#pragma once
#include "Collidable.h"
class Permanent :
	public Collidable, public Seen_Object
{
public:
	Permanent(void);
	~Permanent(void);
};

