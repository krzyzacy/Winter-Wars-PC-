#pragma once
#include "Collidable.h"
#include "Seen_Object.h"

class Structure :
	public Collidable, public Seen_Object
{
public:
	Structure(void);
	~Structure(void);
};

