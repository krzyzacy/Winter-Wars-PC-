#pragma once

#include "Game_Object.h"
#include "Moveable.h"

class Snowball :
	public Game_Object, public Moveable
{
public:
	Snowball(void);
	~Snowball(void);
};

