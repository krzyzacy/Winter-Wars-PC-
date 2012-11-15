#pragma once
#include "Collidable.h"

class Structure :
	public Collidable, public Seen_Object
{
public:
	Structure(void);
	~Structure(void);
};

