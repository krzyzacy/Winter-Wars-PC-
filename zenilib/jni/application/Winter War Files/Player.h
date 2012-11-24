#pragma once
#include "Moveable.h"

class Collision_Table;



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
	void calculate_movement(const Zeni::Vector2f &input_vel);

// Actions
	void throw_ball();

	void update(const float &time);

// Getters
	const Zeni::Camera &get_camera() const
		{return m_camera;}

	virtual const model_key_t get_model_name() const
		{return "player";}
		
	virtual int get_ID() const 
		{return player_ID_c;}

private:
	Zeni::Camera m_camera;


	// Collison Stuff
	Zeni::Collision::Capsule *body;

	const static int player_ID_c;
	friend Collision_Table;
};

