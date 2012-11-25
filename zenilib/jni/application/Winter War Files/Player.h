#pragma once
#include "Moveable.h"

class Collision_Table;

const float Max_Snow_Amount = 1000;
const float charge_rate = 10;
const float pack_rate = 10;

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
	void charge_ball(const float &time);
	/*Takes snow from ground into pack, may need information from world)*/
	void pack_snow(const float &time);

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

	//Snowball Stuff
	float current_radius;
	float Snow_in_Pack; 

	// Collison Stuff
	Zeni::Collision::Capsule *body;

	const static int player_ID_c;
	friend Collision_Table;
};

