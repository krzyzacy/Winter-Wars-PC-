#pragma once

#include "game_object.h"
#include "Moveable.h"

class Snowball :
	public Game_Object, public Moveable
{
public:
	Snowball(void);
	~Snowball(void);
};

