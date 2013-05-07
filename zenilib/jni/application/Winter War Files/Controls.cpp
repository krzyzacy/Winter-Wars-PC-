#include "Controls.h"
#include "Player.h"
#include "Zeni/Joysticks.h"
#include "Game_Model.h"

#include <sstream>

using namespace std;
using namespace Zeni;

const float Cam_factor = 3276800/4;
const int Stick_sensitivity = 8000;
const int Trig_sensitivity = 5000;
const float Move_factor = 32768;

int Controls::Mouse_Camera = 0;


Controls::Controls(bool inverted_, int which_id_)	:
	inverted(inverted_),
	Shoot(CHILL),
	which_id(which_id_), left_last(false), right_last(false), 
	aim_input_sensitivity(1)
{
}

Controls::~Controls(void)
{
}

void Controls::set_inverted(bool invert)	{
	inverted = invert;
}

void Controls::set_input_sensitivity(int _sensitivity)	{
	//Max will make it 4 times as sensitive. 
	// 5 == 1
	// 10 == 4
	// 1 == 1/8

	if(_sensitivity == 1)
		aim_input_sensitivity = 0.2;

	if(_sensitivity >= 2 && _sensitivity <= 7)	
		aim_input_sensitivity = 1 + ((_sensitivity - 5)/4);

	if(_sensitivity >= 8 && _sensitivity <= 10)
		aim_input_sensitivity = _sensitivity - 6;
}

void Controls::check_keyboard_player_change(const SDL_KeyboardEvent &event)	{
	switch(event.keysym.sym)	{
		case SDLK_0:
			Mouse_Camera = -1;
			break;
		case SDLK_1:
			Mouse_Camera = 0;
			break;
		case SDLK_2:
			if(Game_Model::get().num_players_here() >= 2)
				Mouse_Camera = 1;
			break;
		case SDLK_3:
			if(Game_Model::get().num_players_here() >= 3)
				Mouse_Camera = 2;
			break;
		case SDLK_4:
			if(Game_Model::get().num_players_here() >= 4)
				Mouse_Camera = 3;
			break;
		default:
			break;
	}
}

void Controls::take_God_keyboard(const SDL_KeyboardEvent &event)	{
	//Put all global functions that effect the whole game in here, 
	//including things like global variabl adjustment
	//SIN WAVE
}

void Controls::take_mouse_button_input(const SDL_MouseButtonEvent & event)	{

	if(event.button == SDL_BUTTON_LEFT)
		input.shoot = event.state == SDL_PRESSED;
	
	if(event.button == SDL_BUTTON_RIGHT)
		input.Build_Go = event.type == SDL_MOUSEBUTTONDOWN;
	
}

bool Controls::take_keyboard_input(const SDL_KeyboardEvent &event)	{
		//we can incorporate the keyboard (for hacks)
		bool Handled_Input = true;
		


		switch(event.keysym.sym)	{
		case SDLK_w:
			input.Move.y = 1 * Move_factor * (event.type == SDL_KEYDOWN);
			break;
		case SDLK_s:
			input.Move.y = -1 * Move_factor* (event.type == SDL_KEYDOWN);
			break;
		case SDLK_d:
			input.Move.x = -1 * Move_factor* (event.type == SDL_KEYDOWN);
			break;
		case SDLK_a:
			input.Move.x = 1 * Move_factor* (event.type == SDL_KEYDOWN);
			break;
		case SDLK_e:
			input.pack = event.state == SDL_PRESSED;
			break;
		//case SDLK_b:
		//	input.Build_Go = event.state == SDL_PRESSED;
		//	break;
		case SDLK_LSHIFT:
			input.RSHOULDER = event.state == SDL_PRESSED;
			break;
		case SDLK_TAB:
			input.mini_map = event.state == SDL_PRESSED;			
			break;
		//case SDLK_v:
		//	input.LSHOULDER = event.state == SDL_PRESSED;
		//	break;
		case SDLK_t:
			input.tip = event.state == SDL_PRESSED;
			break;
		case SDLK_r:
			input.Tile_up = event.state == SDL_PRESSED;
			break;
		case SDLK_f:
			input.Tile_down = event.state == SDL_PRESSED;
			break;
		case SDLK_SPACE:
			input.jump = event.type == SDL_KEYDOWN;
			break;
		//case SDLK_SPACE:
		//	input.shoot = event.state == SDL_PRESSED;
		//	break;
		default:
			Handled_Input = false;
			break;
		}

		if(input.build_view)	{
			input.Cam.x = input.Move.x;
			input.Cam.y = input.Move.y;				
			input.Move.x = 0;
			input.Move.y = 0;
		}


		return Handled_Input;
}

bool Controls::HandleJoy(const SDL_JoyAxisEvent &event)	{
	//This tracks the triggers and Joysticks
	bool Handled_Input = true;
	Sint16 Val = event.value;
	if(get_Game().joy_mouse.enabled)
		get_Game().joy_mouse.enabled = false;

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
		input.Cam.x = -Val * aim_input_sensitivity;
		break;
	case 3:		//Right Stick up_down
		if(abs(event.value) < Stick_sensitivity)
			Val = 0;
		input.Cam.y = (!inverted - inverted) * Val * aim_input_sensitivity;
		break;
	case 5:		//Left Trigger
		if(Val > Trig_sensitivity)
			input.mini_map = true;
		else
			input.mini_map = false;
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
		input.Tile_up = true;
		input.Tile_down = false;
		break;
	//case SDL_HAT_RIGHTUP:
	//case SDL_HAT_LEFT:     
	case SDL_HAT_CENTERED:
		input.Tile_up = false;
		input.Tile_down = false;
		break;
	//case SDL_HAT_RIGHT:
	//case SDL_HAT_LEFTDOWN:
	case SDL_HAT_DOWN:    
		input.Tile_down = true;
		input.Tile_up = false;
		break;
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
	input.LSHOULDER = false;
	input.RSHOULDER = false;
	bool Handled_Input = true;
	switch(event.button)	{
	case 0: //A Button
		input.jump = event.state == SDL_PRESSED;
		break;
	case 1:	//B Button
		input.pack = event.state == SDL_PRESSED;
		break;
	case 2:	//X Button
		input.Build_Go = event.type == SDL_JOYBUTTONDOWN;
		break;
	case 3:	//Y Button	
		input.tip = event.state == SDL_PRESSED;
		break;
	//	input.jet_pack_mode = event.state == SDL_PRESSED;
//		break;
	case 4:	//Left Shoulder
		if(event.state == SDL_PRESSED && !left_last)	{
			input.LSHOULDER = true;
			left_last = true;
		}
		if(event.state == SDL_RELEASED)
			left_last = false;
		if(event.state == SDL_PRESSED)
			left_last = true;
		break;
	case 5: //Right Shoulder
		if(event.state == SDL_PRESSED && !right_last)	{
			input.RSHOULDER = true;
			right_last = true;
		}
		if(event.state == SDL_RELEASED)
			right_last = false;
		if(event.state == SDL_PRESSED)
			right_last = true;
		break;
	case 6:	//Back button 
		//Respawn?
		break;
	case 7:	//Start Button (Gamestate_Base Handles this for pause only if joymouse enabled)
		get_Game().joy_mouse.enabled = true;
		get_Game().push_state(new Popup_Menu_State());
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
	if(Tron->get_build_view())
		return;

	Tron->adjust_pitch(input.Cam.y/Cam_factor);
	Tron->turn_left(input.Cam.x/Cam_factor);
}

Vector2f Controls::give_movement()	{
	//Vector2f normal_move = input.Move;
	//return normal_move.normalize();
	return input.Move;
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
		Tron->charge_ball();
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
	
	//packing
	if(input.pack)
		Tron->scoop_snow();
	else
		Tron->stop_scooping();

	if (input.tip)
	{
		Tron->next_tip();
		input.tip = false;
	}

	//jumping
	if(input.jump)
		Tron->jump();

	//Alternate Views and Building Menu
	Tron->determine_active_view(input.build_view, input.mini_map);
	//Vector2f norml(input.Cam);
	//Tron->handle_build_menu(norml.normalize());
	if(input.LSHOULDER || input.RSHOULDER)	{
		Tron->handle_struct_type_change(input.LSHOULDER, input.RSHOULDER);
		input.LSHOULDER = false;
		input.RSHOULDER = false;
	}
	
	Tron->Make_Building(input.Build_Go);

	
	//Hacks, for debugging purposes, although would be a good power-up
	Tron->jet_pack_mode(input.jet_pack_mode);

	if(input.Tile_up)
		Tron->raise_tile();
	if(input.Tile_down)
		Tron->lower_tile();

	//Viration Calibration
	if(Tron->vibrate_feedback())	
		Joysticks::get().set_xinput_vibration(which_id, 20, 20);
	else
		Joysticks::get().set_xinput_vibration(which_id, 0, 0);


	Chell = Tron;
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
	ss.str("");

	return status;
}


int Controls::get_cam_to_adjust()	{
	return Mouse_Camera;
}


