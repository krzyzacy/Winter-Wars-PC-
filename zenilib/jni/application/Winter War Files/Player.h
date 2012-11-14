#pragma once
#include "Game_Object.h"
#include "Moveable.h"

class Player :
	public Moveable
{
public:
	Player(void);
	~Player(void);

// camera functions
	void turn_left(float theta);
	void adjust_pitch(float phi);

// Moving Functions
	void move_forward(float force);
	void move_left(float force);

// Actions
	void throw_ball();


// Getters
	const Zeni::Camera &get_camera() const
		{return m_camera;}

private:
	Zeni::Camera m_camera;
};

