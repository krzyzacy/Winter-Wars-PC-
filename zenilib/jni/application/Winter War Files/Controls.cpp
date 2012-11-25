#include "Controls.h"
#include "Player.h"

#include <sstream>

using namespace std;
using namespace Zeni;

Controls::Controls(bool inverted_)	:
	inverted(inverted_),
	Shoot(CHILL)
{
}

Controls::~Controls(void)
{
}

void Controls::set_inverted(bool invert)	{
	inverted = invert;
}

bool Controls::take_keyboard_input(const SDL_KeyboardEvent &event, const int which)	{
	//MOVE?RENAME FOR KEYBOARD
		//we can incorporate the keyboard (for hacks)
		bool Handled_Input = true;
		if(which == 0)	{
			switch(event.keysym.sym)	{
			case SDLK_w:
				input.Move.y = 1 * (event.type == SDL_KEYDOWN);
				break;
			case SDLK_s:
				input.Move.y = -1 * (event.type == SDL_KEYDOWN);
				break;
			case SDLK_d:
				input.Move.x = -1 * (event.type == SDL_KEYDOWN);
				break;
			case SDLK_a:
				input.Move.x = 1 * (event.type == SDL_KEYDOWN);
				break;
			case SDLK_RETURN:
				input.shoot = event.state == SDL_PRESSED;
				
			default:
				Handled_Input = false;
				break;
			}
		}
		else if(which == 1)	{
			switch(event.keysym.sym)	{
			case SDLK_UP:
				input.Move.y = 1 * (event.type == SDL_KEYDOWN);
				break;
			case SDLK_DOWN:
				input.Move.y = -1 * (event.type == SDL_KEYDOWN);
				break;
			case SDLK_LEFT:
				input.Move.x = 1 * (event.type == SDL_KEYDOWN);
				break;
			case SDLK_RIGHT:
				input.Move.x = -1 * (event.type == SDL_KEYDOWN);
				break;
			default:
				Handled_Input = false;
				break;
			}
		}
		else	
			Handled_Input = false;

		return Handled_Input;
}


bool Controls::HandleJoy(const SDL_JoyAxisEvent &event)	{
	//This tracks the triggers and Joysticks
	bool Handled_Input = true;
	Sint16 Val = event.value;
	

	switch(event.axis)	{
	case 0:		//Left Stick left-right
		if(abs(event.value) < Stick_sensitivity)
			Val = 0;
		input.Move.x = -Val;
		break;
	case 1:		//Left Stick up_down
		if(abs(event.value) < Stick_sensitivity)
			Val = 0;
		input.Move.y = -Val;
		break;
	case 4:		//Right Stick left-right
		if(abs(event.value) < Stick_sensitivity)
			Val = 0;
		input.Cam.x = -Val;
		break;
	case 3:		//Right Stick up_down
		if(abs(event.value) < Stick_sensitivity)
			Val = 0;
		input.Cam.y = (!inverted - inverted) * Val;
		break;
	case 5:		//Left Trigger
		if(Val > Trig_sensitivity)
			input.build_view = true;
		else
			input.build_view = false;
		break;
	case 2:		//Right Trigger
			if(Val > Trig_sensitivity) //Anything greater than 0 represents a press (32768 is max)
				input.shoot = true;
			else 
				input.shoot = false;
		break;
	default:
		Handled_Input = false;
		break;
	}
	return Handled_Input;
}


bool Controls::HandleJoy(const SDL_JoyHatEvent &event)	{
	//this discretely tracks the dpad
	//Currently unused
	bool Handled_Input = false;
	switch(event.value)	{
	//case SDL_HAT_LEFTUP:
	case SDL_HAT_UP:    
		Handled_Input = true;
	//case SDL_HAT_RIGHTUP:
	//case SDL_HAT_LEFT:     
	//case SDL_HAT_CENTERED:
	//case SDL_HAT_RIGHT:
	//case SDL_HAT_LEFTDOWN:
	//case SDL_HAT_DOWN:    
	//case SDL_HAT_RIGHTDOWN:
	default:
		Handled_Input = false;
		break;
	}
	return Handled_Input;
}

bool Controls::HandleJoy(const SDL_JoyButtonEvent &event)	{	
	//This tracks the buttons on the controller
	//including the shoulders
	bool Handled_Input = true;
	switch(event.button)	{
	case 0: //A Button
		input.jump = event.state == SDL_PRESSED;
		break;
	case 1:	//B Button
		input.pack = event.state == SDL_PRESSED;
		break;
	case 2:	//X Button
		//No Function (Ice Pick)?
		break;
	case 3:	//Y Button
		//No Funciton
		break;
	case 4:	//Left Shoulder
		input.mini_map = event.state == SDL_PRESSED;
		break;
	case 5: //Right Shoulder

		break;
	case 6:	//Back button 
		//Respawn?
		break;
	case 7:	//Start Button (Gamestate_Base Handles this for pause only if joymouse enabled)
		get_Game().joy_mouse.enabled = true;
		Handled_Input = false;
		break;
	case 8:	//Click left joystick down
	case 9:	//Click right joystick down
	default:
		Handled_Input = false;
		break;
	}
	return Handled_Input;
}

void Controls::adjust_Cam(Player* Tron)	{
	Tron->adjust_pitch(input.Cam.y/Cam_factor);
	Tron->turn_left(input.Cam.x/Cam_factor);
}

Vector2f Controls::give_movement()	{
	Vector2f normal_move = input.Move;
	return normal_move.normalize();
}

void Controls::interact_with_player(Player* Tron, const float &time)	{
	//First deal with shooting state
	switch(Shoot)		{
	case CHILL:
		//Check for charge command, else do nothing
		if(input.shoot)
			Shoot = CHARGING;
		break;
	case CHARGING:
		Tron->charge_ball(time);
		if(!input.shoot)
			Shoot = FIRE;
		break;
	case FIRE:
		Tron->throw_ball();
		Shoot = CHILL;
		break;
	default:
		Shoot = CHILL;
		break;
	}

//Then deal with buttons, might have to split off here
	//Then Deal with jump?	(requires player/world info (is in air))
	//Then deal with pack(Absorb snow) (requires world info)
	//Deal with mini-map view
	//deal with build view
	
	if(input.pack)
		Tron->pack_snow(time);

	//Chell = Tron;
	
}

string Controls::give_stick_status()	{
	string status = ""; 
	ostringstream ss;
	//ss << input.Move.x;
	//status += ss.str();
	//ss.str("");
	//status += " Move_Y: ";
	//ss << input.Move.y;
	//status += ss.str();
	//ss.str("");

	//status = "Snow: ";
	//ss << Chell->Snow_in_Pack;
	//status += ss.str();
	//ss.str("");
	//status += " radius: ";
	//ss << Chell->current_radius;
	//status += ss.str();
	//ss.str("");
	//status += "Shoot state: ";
	//ss << Shoot;
	//status += ss.str();
	//ss.str("");

	return status;
}


