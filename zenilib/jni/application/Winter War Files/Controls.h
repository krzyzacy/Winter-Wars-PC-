#pragma once

#include <zenilib.h>


class Player;

enum	Shooting_State	{
		CHILL, CHARGING, FIRE
};



class Controls
{
public:
	Controls(bool inverted_ = false, int which_id_ = 0);
	~Controls(void);
	
	std::string give_stick_status();

	bool take_keyboard_input(const SDL_KeyboardEvent &event, const int which);

	bool HandleJoy(const SDL_JoyAxisEvent &event);
	bool HandleJoy(const SDL_JoyHatEvent &event);
	bool HandleJoy(const SDL_JoyButtonEvent &event);

	/*		This function translates most control inputs into actions
		Doesn't handle joystics, might split up into buttons and triggers*/
	void interact_with_player(Player* Tron, const float &time);

	/* Adjust player view using right stick	*/
	void adjust_Cam(Player* Tron);

	int get_cam_to_adjust();

	void reset_Cam()	{
		input.Cam.x = 0;
		input.Cam.y = 0;
	}


	/*	Sets inverted if the player changes options menu (options to be implemented */
	void set_inverted(bool invert);

	Zeni::Vector2f give_movement();

private:

	struct Inputs	{
		Inputs()	: jump(false), pack(false), mini_map(false), shoot(false), 
		build_view(false), Cam(0.0f, 0.0f), Move(0.0f, 0.0f), RSHOULDER(false), LSHOULDER(false),
		Tile_up(false), Tile_down(false), Build_Go(false), jet_pack_mode(false)		{}

		bool jump;				//A button
		bool pack;				//B button
		bool mini_map;		//left shoulder
		bool shoot;				//Right trigger
		bool build_view;	//left trigger

		bool RSHOULDER;		//&&&Right shoulder, only temporary
		bool LSHOULDER;
		bool Build_Go;
		bool Tile_up;
		bool Tile_down;

		bool jet_pack_mode;

		Zeni::Vector2f		Cam;
		Zeni::Vector2f		Move;

	} input;

	bool inverted;
	bool left_last;
	bool right_last;


	Shooting_State	Shoot;
	int Mouse_Camera;

	int which_id;

	//Temp Pointer (or not????)
	Player * Chell;

};

