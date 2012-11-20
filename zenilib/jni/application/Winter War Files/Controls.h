#pragma once

#include <zenilib.h>

const float Cam_factor = 3276800;
const int Stick_sensitivity = 8000;

class Player;


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

	void adjust_Cam(Player* Tron);

	void set_inverted(bool invert);

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

};

