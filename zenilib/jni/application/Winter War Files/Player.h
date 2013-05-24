#pragma once
#include "Elf.h"
#include "Utility.h"
#include "Stats.h"

#include <Zeni/Sound.h>

class Collision_Table;

extern std::vector<Zeni::String> tips;

struct Message
{
	/*priorities*/
// instructional = 0
// tip = 1
// you choose rest
	Message(const Zeni::String &msg_ = "", int priority_ = 0, float time_ = -1) :
		msg(msg_), priority(priority_), time(time_)
		{timer.start();}

	bool is_over() const
		{ return (time - timer.seconds()) < 0;}

	Zeni::String msg;
	int priority;
private:
	Zeni::Chronometer<Zeni::Time> timer;
	float time;
};


class Player :	public Elf	{
public:
	//Player(const Zeni::Point3f &center_ = Zeni::Point3f(0,0,10));
	Player(Team* team_, const std::string &gender_);
	~Player(void);

//Camera functions
	void turn_left(float theta);
	void adjust_pitch(float phi);
	
//Movement
	void calculate_movement(const Zeni::Vector2f input_vel);	//Friction is controlled here
	void off_map();
	void hit_tile();
	void on_ground();


	void handle_struct_type_change(bool Left, bool Right);
	//void handle_build_menu(const Zeni::Vector2f &norml_stick);
	void determine_active_view(bool build, bool mini);
	
	bool get_mini_view() const {return mini_open;}
	bool get_build_view() const {return (build_open && !mini_open);}
	float get_stick_choice() const {return stick_theta;} //obsolete
	
	void change_z(const float &delta)	{center.z += delta;}

	void update(const float &time);

	void get_damaged(float damage);
	void throw_ball();
	void charge_ball();
	virtual bool create_building(Structure_Type	Building);
	virtual void Make_Building(bool go);


	bool vibrate_feedback();

// Getters
	const Zeni::Point3f &get_position() const {return center;}

	const Zeni::Camera &get_camera() const
		{return m_camera;}

	//virtual const model_key_t get_model_name() const;

	virtual int get_ID() const 
		{return player_ID_c;}
	
	Structure_Type	select_type(const Zeni::Vector2f &stick);

// Messages
	/* Adds a message for the player */
	void add_message(const Zeni::String &, int priority = 0, float seconds = 3);
	
	void next_tip();
	void reset_tips();

	/* true if there is a message*/
	bool has_message() const;

	/* Gets most important message for player */
	Zeni::String get_message() const;


// Stats
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

// Collision Body
	void create_body();

	bool allowed_to_calculate_movement;

	static int max_id;
private: 
	int ID;

	int cur_tip;

	Zeni::Camera m_camera;
		
	float stick_theta; //This is obsolete. But will cause a compiler error

	Zeni::Chronometer<Zeni::Time> ShakeTime;	//Controller Vibration Timer
	
	/* "" if no message */  
	Message message;

	bool mini_open;
	bool build_open;
	
	const static int player_ID_c;
	friend Collision_Table;
};

