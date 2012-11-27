#pragma once
#include "Moveable.h"

class Collision_Table;
class Team;

extern const float Max_Snow_Amount;	
extern const float Max_Player_Health;
extern const float packing_rate;					//Rate at which snowball is packed
extern const float snow_depletion_rate;		//Rate at which snow is consumed while packing
extern const float snow_absorbtion_rate;	//Rate of filling snow meter from tile

enum Jump_State	{
	ON_GROUND, BOOST, FALLING_WITH_STYLE, JET_PACK
};


class Player :	public Moveable		{
public:
	Player(const Zeni::Point3f &center_ = Zeni::Point3f(0,0,10));
	~Player(void);

	void set_Team(Team *myTeam_)	{myTeam = myTeam_;}

// camera functions
	void turn_left(float theta);
	void adjust_pitch(float phi);

// Moving Functions
	void calculate_movement(const Zeni::Vector2f &input_vel);

// Actions
	void throw_ball();
	void charge_ball();
	/*Takes snow from ground into pack, may need information from world)*/
	void pack_snow();
	void jump();

	void update(const float &time);

// Getters
	const Zeni::Camera &get_camera() const
		{return m_camera;}

	virtual const model_key_t get_model_name() const
		{return "player";}
		
	virtual int get_ID() const 
		{return player_ID_c;}

	float get_Snow() const {return Snow_in_Pack;}
	float get_Health() const {return health;}
	int get_Team_Blocks() const;

// Collision Body
	void create_body();

private: 
	Zeni::Camera m_camera;

	//Snowball and Player Stuff
	float current_radius;
	float Snow_in_Pack; 
	float health;
	Team * myTeam;

	Jump_State	Jumping;
	Zeni::Chronometer<Zeni::Time> AirTime;

	// Collison Stuff
	Zeni::Collision::Capsule body;

	const static int player_ID_c;
	friend Collision_Table;
};

