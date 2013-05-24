#pragma once

#include "Moveable.h"
#include "Utility.h"
#include "Stats.h"

#include <Zeni/Sound.h>


class Team;
class Tile;
class PlayerAnimator;
enum PlayerEvent_e;

extern float standard_speed;

extern float Max_Snow_Amount;			// most you can scoop/reload
extern float Max_Player_Health;
extern float max_snowball_size;			// most you can pack/charge	
extern float packing_rate;				// Rate at which snowball is packed
extern float snow_depletion_rate;		// Rate at which snow is consumed while packing
extern float snow_absorbtion_rate;		// Rate of filling snow meter from tile
extern float Building_Recharge_Time;	// Time it takes in between builds
extern float Max_Stick_Input;
extern float Respawn_Time;

extern float Stick_Accel;	//Don't Touch. Part of movement Physics, poorly named

enum Jump_State	{
	ON_GROUND, BOOST, FALLING_WITH_STYLE, JET_PACK
};

enum Build_State	{
	REST, RECHARGE_BUILD
};

enum Shooting_State	{
	CHILL, CHARGING, FIRE
};

/*
 * An Elf Represnts an in game elf that has a model and can do elf things
 * there can be player elves and ai elves, these inherit from elf.
 */
class Elf : public Moveable		{
	
//First All the data Members
private:
	std::string gender;

protected: 
	float current_radius;	//size of the snowball currently being packed
	float Snow_in_Pack;		//Snow left in the elfs pack
	float health;			//The elfs current Health
	float hit_timer;		//floats instead of timers????
	float throw_timer;
	float packing_timer;

	Team * myTeam;			//The Team that this elf is on

//Movement
	Zeni::Point3f backup;   
	bool allowed_to_calculate_movement;
	Zeni::Chronometer<Zeni::Time> Player_Movement_Message_Ticker;

//Jumping State Machine
	Jump_State	Jumping;
	Zeni::Chronometer<Zeni::Time> AirTime;

//Shooting State Machine
	Shooting_State	Shoot;
	
//Building State Machine
	Build_State	Builder;
	Zeni::Chronometer<Zeni::Time> BuildTime;
	Structure_Type Selection;

	Zeni::Chronometer<Zeni::Time> Deathclock;	//Respawn Clock
	bool dead_mode;								//Respawn boolean

	virtual void off_map() {}
	virtual void hit_tile() {}
	virtual void on_ground() {}

	// Collison Stuff
	Zeni::Collision::Capsule body;
	
// Animation
	PlayerAnimator *animation_state;
	Animator *get_animator() const;

	
//Sound
	int sound_choice;
	Zeni::Sound_Source * player_boy_hit;
	Zeni::Sound_Source * player_girl_hit;
	Zeni::Sound_Source * snowball_hit1;
	Zeni::Sound_Source * snowball_hit2;
	Zeni::Sound_Source * player_dead;

public:

// Stats
	static int max_id;
	int ID; 

	struct Player_Stats : public Stats
	{
		Player_Stats(int id);

		int kills;
		int friendly_kills;
		int deaths;
		int thrown;
		int hit;
		int tips;
		int biggest_snowball;
		int num_large_snowballs;
		int num_small_snowballs;
		int tiles_raised;
		int tiles_lowered;
		int amount_scooped;
		int friendly_hit;
		int snow_used;
		int built;
		int destroyed;
		int damage_taken;
		int damage_dealt;
	}stats;


//All the Functions of Elf
private:
protected:
public:
	//Constructor First -- This will take some thinking, 
	//multiple constrcutors?? perhaps
	//Team should definitely be in the constructor, and then kill set team
	Elf(Team* team_, const std::string &gender_);
	~Elf(void);

// Moving Functions 
	virtual void calculate_movement(const Zeni::Vector2f input_vel);	//Friction is controlled here
	virtual void push_away_from(Zeni::Point3f &obstacle, const float force = 100);
	virtual void teleport(Zeni::Point3f p)	{ center = p; }

// Actions
	virtual void manage_shooting_state(bool shoot_input);
	virtual void throw_ball();
	virtual void charge_ball();
	virtual void scoop_snow(); /*SCOOP - Takes snow from ground into pack*/
	virtual void stop_scooping();
	virtual void jump();
	virtual void jet_pack_mode(bool state);
	//Building Functions %%%% De Clutter Building to one function (callled by build button)
	Structure_Type get_current_choice()	const {return Selection;}
	virtual bool create_building(Structure_Type	Building);
	virtual void Make_Building(bool go);
	//Tiles
	virtual void raise_tile();
	virtual void stop_raising();
	virtual void lower_tile();
	virtual void stop_lowering();
	//Respawn/Death
	virtual void player_death();
	virtual void respawn();
	bool is_player_KO() const {return dead_mode;}
	//Take damage as well as heal
	virtual void healing_waters(float health_up);
	virtual void get_damaged(float damage);

//Getters/Setters
	//HUD stuff
	float get_hit_timer() const		{return hit_timer;}
	float get_throw_timer() const	{return throw_timer;}
	float get_packing_timer() const {return packing_timer;}
	bool is_packing() const			{ return current_radius > 0.0f? true : false ;}
	float get_Snow() const			{return Snow_in_Pack;}
	float get_Health() const		{return health;}
	float get_time_until_respawn() const {return Respawn_Time - Deathclock.seconds();	}
	std::string get_gender() const	{return gender;}
	//Team Stuff
	int get_Team_Blocks() const;		
	int get_Team_Resource_Rate() const;
	int get_Team_Index() const;
	Team * get_team() const			{return myTeam;}
	
//Collision Body
	virtual void create_body();

//Sound
	virtual void play_sound();
	virtual void switch_state(PlayerEvent_e);

	virtual const model_key_t get_model_name() const;
	virtual void update(const float &time);
};
