#pragma once
#include "Collidable.h"
#include "Seen_Object.h"

class Permanent :
	public Collidable, public Seen_Object
{
public:
	Permanent(void);
	~Permanent(void);
};

