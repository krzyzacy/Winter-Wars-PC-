#pragma once
#include "game_object.h"
#include "Moveable.h"

class Player :
	public Game_Object,
	public Moveable
{
public:
	Player(void);
	~Player(void);
};

