#pragma once
#include "Moveable.h"
#include "Structure.h"

class Collision_Table;
class Team;
class Tile;
class PlayerAnimator;
enum PlayerEvent_e;

extern const float Max_Snow_Amount;	
extern const float Max_Player_Health;
extern const float packing_rate;			//Rate at which snowball is packed
extern const float snow_depletion_rate;		//Rate at which snow is consumed while packing
extern const float snow_absorbtion_rate;	//Rate of filling snow meter from tile

extern const float Building_Recharge_Time;
extern const int Max_Stick_Input;
extern const float Tile_Move_Speed;
extern const float Respawn_Time;

enum Jump_State	{
	ON_GROUND, BOOST, FALLING_WITH_STYLE, JET_PACK
};

enum Build_State	{
		REST, SELECT_BUILDING, CREATE_BUILDING, RECHARGE_BUILD
};



class Player :	public Moveable		{
public:
	Player(const Zeni::Point3f &center_ = Zeni::Point3f(0,0,10));
	~Player(void);

	void set_Team(Team *myTeam_)	{myTeam = myTeam_;}
	void set_Gender(const std::string &gender_) {gender = gender_;}
	std::string get_Gender() const {return gender;}

// camera functions
	void turn_left(float theta);
	void adjust_pitch(float phi);

// Moving Functions
	void calculate_movement(const Zeni::Vector2f &input_vel);
	void push_away_from(Zeni::Point3f &obstacle, const float force = 100);

// Actions
	void throw_ball();
	void charge_ball();
	/*Takes snow from ground into pack, may need information from world)*/
	void pack_snow();
	void stop_scooping();
	void jump();
	void jet_pack_mode(bool state);
	
	void handle_build_menu(const Zeni::Vector2f &norml_stick);
	void determine_active_view(bool build, bool mini);
	
	bool get_mini_view() const {return mini_open;}
	bool get_build_view() const {return (build_open && !mini_open);}
	float get_stick_choice() const {return stick_theta;}
	bool create_building(Structure_Type	Building);
	
	void raise_tile();
	void lower_tile();
	void change_z(const float &delta)	{center.z += delta;}


	void update(const float &time);
	void player_death();
	void respawn();
	bool is_player_KO() const {return dead_mode;}
	void healing_waters(float health_up);


	void get_damaged(float damage);
	bool vibrate_feedback();

// Getters
	const Zeni::Point3f &get_posistion() const {return center;}

	const Zeni::Camera &get_camera() const
		{return m_camera;}

	virtual const model_key_t get_model_name() const;

	virtual int get_ID() const 
		{return player_ID_c;}

	float get_Snow() const {return Snow_in_Pack;}
	float get_Health() const {return health;}
	int get_Team_Blocks() const;
	float get_time_until_respawn()	const {return Respawn_Time - Deathklok.seconds();	}
	int get_Team_Index() const;
	std::string get_gender() const	{return gender;}
	Team * get_team() const {return myTeam;}

	Structure_Type	select_type(const Zeni::Vector2f &stick);

// HUD stuff
	float get_hit_timer() const {return hit_timer;}
	float get_throw_timer() const {return throw_timer;}
	bool is_packing() const { return current_radius > 0.0f? true : false ;}

// Messages
	/* Adds a message for the player */
	void add_message(const Zeni::String &);

	/* true if there is a message*/
	bool has_message();

	/* Gets most important message for player */
	Zeni::String get_message();

// Collision Body
	void create_body();

private: 
	Zeni::Camera m_camera;

	//Snowball and Player Stuff
	float current_radius;
	float Snow_in_Pack; 
	float health;

	std::string gender;

	Team * myTeam;
	Zeni::Point3f backup;

	Jump_State	Jumping;
	Zeni::Chronometer<Zeni::Time> AirTime;

	Build_State	Builder;
	Zeni::Chronometer<Zeni::Time> BuildTime;
	Structure_Type Selection;
	float stick_theta;

	Zeni::Chronometer<Zeni::Time> ShakeTime;
	Zeni::Chronometer<Zeni::Time> Deathklok;

	/* "" if no message */
	Zeni::String message;

	bool mini_open;
	bool build_open;
	bool dead_mode;

	float hit_timer;
	float throw_timer;

	virtual void off_map();
	virtual void hit_tile();
	virtual void on_ground();

	// Animation
	PlayerAnimator *animation_state;
	Animator *get_animator() const;
	void switch_state(PlayerEvent_e);

	// Collison Stuff
	Zeni::Collision::Capsule body;

	const static int player_ID_c;
	friend Collision_Table;
};

