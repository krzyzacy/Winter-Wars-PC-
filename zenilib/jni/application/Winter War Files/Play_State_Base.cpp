#include "Play_State_Base.h"

#include "Game_Model.h"

Play_State_Base::Play_State_Base()	:
	m_prev_clear_color(get_Video().get_clear_Color())
	,test()	, time_passed(0.0f)
	
{
		PlayTime.start();
		set_pausable(true);

		//Control Stuff (presently for one controller)
		//set_action(Zeni_Input_ID(SDL_JOYAXISMOTION, Joysticks::AXIS_LEFT_THUMB_X), LSTICK_X);
		//set_action(Zeni_Input_ID(SDL_JOYAXISMOTION, Joysticks::AXIS_LEFT_THUMB_Y), LSTICK_Y);
		//set_action(Zeni_Input_ID(SDL_JOYAXISMOTION, Joysticks::AXIS_RIGHT_THUMB_X), RSTICK_X);
		//set_action(Zeni_Input_ID(SDL_JOYAXISMOTION, Joysticks::AXIS_RIGHT_THUMB_Y), RSTICK_Y);
		//set_action(Zeni_Input_ID(SDL_JOYAXISMOTION, Joysticks::AXIS_LEFT_TRIGGER), L_TRIG);
		//set_action(Zeni_Input_ID(SDL_JOYAXISMOTION, Joysticks::AXIS_RIGHT_TRIGGER), R_TRIG);

		//set_action(Zeni_Input_ID(SDL_JOYBUTTONUP, Joysticks::BUTTON_A), RELEASE_A);
		//set_action(Zeni_Input_ID(SDL_JOYBUTTONDOWN, Joysticks::BUTTON_A), PRESS_A);

}

Play_State_Base::~Play_State_Base()	 {

}

void Play_State_Base::on_push()	{
		get_Window().mouse_hide(true);
		get_Window().mouse_grab(true);
			
		get_Video().set_clear_Color(Color(0,.1,.1,.1));
}

void Play_State_Base::on_pop()	{
		get_Window().mouse_hide(false);
		get_Window().mouse_grab(false);
		get_Video().set_clear_Color(m_prev_clear_color);
    //get_Game().joy_mouse.enabled = true;
}

void Play_State_Base::on_key(const SDL_KeyboardEvent &event) {
		switch(event.keysym.sym) {
		  default:
			Gamestate_Base::on_key(event); // Let Gamestate_Base handle it
			break;
		}
} 

void Play_State_Base::on_event(const SDL_Event &event)	{
		if(!test.take_input(event))
			Gamestate_Base::on_event(event);
}
	
//void Play_State_Base::on_event(const Zeni_Input_ID &Zid, const float &confidence, const int &action)	{
//		if(!test.take_input(Zid, confidence, action))
//			Gamestate_Base::on_event(Zid, confidence, action);
//}

void Play_State_Base::on_mouse_motion(const SDL_MouseMotionEvent &event) {
			
	for (int i = 0 ; i < 4 ; i++)
	{
		Game_Model::get().get_player(i)->adjust_pitch(event.yrel / 500.0f);
		Game_Model::get().get_player(i)->turn_left(-event.xrel / 500.0f);    
	}
}

void Play_State_Base::on_joy_axis(const SDL_JoyAxisEvent &event)	{
	if(!test.HandleJoy(event))
		Gamestate_Base::on_joy_axis(event);
}

void Play_State_Base::on_joy_ball(const SDL_JoyBallEvent &event)	{
	if(!test.HandleJoy(event))
		Gamestate_Base::on_joy_ball(event);
}

void Play_State_Base::on_joy_hat(const SDL_JoyHatEvent &event)	{
	if(!test.HandleJoy(event))
		Gamestate_Base::on_joy_hat(event);
}

void Play_State_Base::on_joy_button(const SDL_JoyButtonEvent &event)	{
	if(!test.HandleJoy(event))
		Gamestate_Base::on_joy_button(event);
}



void Play_State_Base::perform_logic()	
{
	
	const float frametime_passed = PlayTime.seconds();
	const float currentStep = frametime_passed - time_passed;
	time_passed = frametime_passed;
	time_step = currentStep;


// THis needs to be moved inside of Controls!!!!  Put the player in controls
	Game_Model::get().get_player(0)->adjust_pitch(test.input.right_y/100.0f);
	Game_Model::get().get_player(0)->turn_left(test.input.right_x/100.0f);
	

	Game_Model::get().get_player(0)->move_strafe(time_step, 100, Vector3f(test.input.left_x, test.input.left_y, 0));

	Game_Model::get().update();
}

void Play_State_Base::render()	{
	Game_Model::get().render();
}
