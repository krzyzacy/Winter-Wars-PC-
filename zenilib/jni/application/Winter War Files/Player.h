#pragma once
#include "Game_Object.h"
#include "Moveable.h"

class Player :
	public Moveable
{
public:
	Player(void);
	~Player(void);

	void turn_left(float theta);
	void adjust_pitch(float phi);

	void move_forward(float force);
	void move_left(float force);
	
	void throw_ball();

};

