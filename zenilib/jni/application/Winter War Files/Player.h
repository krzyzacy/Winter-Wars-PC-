#pragma once
#include "Moveable.h"

class Player :
	public Moveable
{
public:
	Player(const Zeni::Point3f &center_ = Zeni::Point3f(0,0,10));
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
	

	const model_key_t get_model_name() const
		{return "player";}
private:
	Zeni::Camera m_camera;
};

