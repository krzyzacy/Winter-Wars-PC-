#pragma once

#include <zenilib.h>


class Player;

enum	Shooting_State	{
		CHILL, CHARGING, FIRE
};


class Controls
{
public:
	Controls(bool inverted_ = false);
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

	/*	Sets inverted if the player changes options menu (options to be implemented */
	void set_inverted(bool invert);

	Zeni::Vector2f give_movement();

private:

	struct Inputs	{
		Inputs()	: jump(false), pack(false), mini_map(false), shoot(false), 
			build_view(false), Cam(0.0f, 0.0f), Move(0.0f, 0.0f)		{}

		bool jump;				//A button
		bool pack;				//B button
		bool mini_map;		//left shoulder
		bool shoot;				//Right trigger
		bool build_view;	//left trigger

		Zeni::Vector2f		Cam;
		Zeni::Vector2f		Move;

	} input;

	bool inverted;

	Shooting_State	Shoot;
	int Mouse_Camera;

	//Temp Pointer (or not????)
	Player * Chell;

};

