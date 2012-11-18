#include "Play_State_Base.h"

Play_State_Base::Play_State_Base()	:
	time_passed(0.0f)
	, m_next(false)
	, escape(false)
	, m_prev_clear_color(get_Video().get_clear_Color())
	, Perm(Point3f(30,10,0), Vector3f(2,2,2))
	,Rend(Point3f(1,0,20))
	,Rend2(Point3f(10,30,100))
	,Rend3(Point3f(0,0,50))
	,Rend4(Point3f(10,10,20))
	,test()
{
		set_pausable(true);
		PlayTime.start();
		view.add_renderable(&Rend);
		view.add_player_view(new Player_View(&Rend));
		view.add_renderable(&Rend2);
		view.add_player_view(new Player_View(&Rend2));
		view.add_renderable(&Rend3);
		view.add_player_view(new Player_View(&Rend3));
		view.add_renderable(&Rend4);
		view.add_player_view(new Player_View(&Rend4));
		view.add_renderable(&Perm);



		//Control Stuff (presently for one controller)
		
		set_action(Zeni_Input_ID(SDL_JOYAXISMOTION, Joysticks::AXIS_LEFT_THUMB_X), LSTICK_X);
		set_action(Zeni_Input_ID(SDL_JOYAXISMOTION, Joysticks::AXIS_LEFT_THUMB_Y), LSTICK_Y);
		set_action(Zeni_Input_ID(SDL_JOYAXISMOTION, Joysticks::AXIS_RIGHT_THUMB_X), RSTICK_X);
		set_action(Zeni_Input_ID(SDL_JOYAXISMOTION, Joysticks::AXIS_RIGHT_THUMB_Y), RSTICK_Y);
		set_action(Zeni_Input_ID(SDL_JOYAXISMOTION, Joysticks::AXIS_LEFT_TRIGGER), L_TRIG);
		set_action(Zeni_Input_ID(SDL_JOYAXISMOTION, Joysticks::AXIS_RIGHT_TRIGGER), R_TRIG);

		set_action(Zeni_Input_ID(SDL_JOYBUTTONUP, Joysticks::BUTTON_A), RELEASE_A);
		set_action(Zeni_Input_ID(SDL_JOYBUTTONDOWN, Joysticks::BUTTON_A), PRESS_A);

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
			Gamestate_II::on_key(event); // Let Gamestate_II handle it
			break;
		}
} 

void Play_State_Base::on_event(const SDL_Event &event)	{
		//Yes I realize this does nothing right now, but it is where
		//we can incorporate the keyboard (for hacks)

			Gamestate_II::on_event(event);

}
	
void Play_State_Base::on_event(const Zeni_Input_ID &Zid, const float &confidence, const int &action)	{
		switch(action)	{

		case L_TRIG:
			//currently left trigger pressed so do something
			test.input.build_view = true;
			test.input.jump = true;
			break;
		case R_TRIG:
			
			break;

		
		case RSTICK_X:
			test.input.right_x = confidence;
			break;
		case RSTICK_Y:
			test.input.right_y = confidence;
			break;
		case LSTICK_X:
			test.input.left_x = confidence;
			break;
		case LSTICK_Y:
			test.input.left_y = confidence;
			break;

		default:
			Gamestate_II::on_event(Zid, confidence, action);
			break;
		}

}

/*void Play_State_Base::on_mouse_motion(const SDL_MouseMotionEvent &event) {
			Rend.adjust_pitch(event.yrel / 500.0f);
			Rend.turn_left(-event.xrel / 500.0f);    

			Rend2.adjust_pitch(event.yrel / 500.0f);
			Rend2.turn_left(-event.xrel / 500.0f);   

			Rend3.adjust_pitch(event.yrel / 500.0f);
			Rend3.turn_left(-event.xrel / 500.0f);  

			Rend4.adjust_pitch(event.yrel / 500.0f);
			Rend4.turn_left(-event.xrel / 500.0f);
}*/

void Play_State_Base::perform_logic()	
{
	const float frametime_passed = PlayTime.seconds();
	const float currentStep = frametime_passed - time_passed;
	time_passed = frametime_passed;
	time_step = currentStep;

	Rend.adjust_pitch(test.input.right_y/100.0f);
	Rend.turn_left(test.input.right_x/100.0f);

	Rend.move_strafe(time_step, 100, Vector3f(test.input.left_x, test.input.left_y, 0));
	

}

void Play_State_Base::render()	{
	Video &vr = get_Video();	
	if(test.input.jump)
		view.render();
}
