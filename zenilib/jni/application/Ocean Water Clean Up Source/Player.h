#pragma once

#include "Game_Object.h"

#include <list>

class Snowball;
class Collision_Table;

class Player :
	public Game_Object
{
public:
	Player(const Zeni::Point2f &position_);

	~Player(void);
		
	void update();

	void render() const;

	virtual int get_ID() const 
		{return player_ID_c;}

	int get_score()
		{return score;}

	void add_points(int points)
		{score += points;}
	
	Zeni::Model *get_m() const
		{return NULL;}

	void render_hud() const;

	void throw_ball();
	void pack_ball();
	void finish_packing();

	void move_back()
	{ m_pos = old_pos;}

	Zeni::Camera m_camera;
    void adjust_pitch(const float &phi);
    void turn_left_xy(const float &theta);

	struct Controls {
      Controls() : forward(false), left(false), back(false), right(false)
		  , finish_pack(false), pack(false), throw_ball(false), packed(false) {}

      bool forward;
      bool left;
      bool back;
      bool right;
	  bool pack; // true if button is down.
	  bool throw_ball;
	  bool finish_pack;
	  bool packed;  // true if i have been packing

    } m_controls;

protected:
	static int num_players;
	int num;

	virtual int get_parent_ID() const
		{return Game_Object::get_ID();}

private:
	const static int player_ID_c;

	std::list<Snowball*> snowballs;
	float being_packed;  //size of snowball being packed

	int score;

	Zeni::Point3f old_pos;

	void update_camera_pos();
	
	friend Collision_Table;
};


