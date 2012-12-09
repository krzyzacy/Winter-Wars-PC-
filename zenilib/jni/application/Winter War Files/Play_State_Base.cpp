#include "Play_State_Base.h"

#include "Game_Model.h"

#include "Controls.h"
#include "View.h"
#include "Player.h"
#include "Player_View.h"
#include "Permanent.h"
#include "Team.h"

Play_State_Base::Play_State_Base(const vector<String> &genders_, const vector<int> &colors_, const vector<int> &controls_)	:
	m_prev_clear_color(get_Video().get_clear_Color()),
	genders(genders_),
	teams(colors_)
{		
		set_pausable(true);
		for(int i = 0; i < 4; i++)	{
			controllers.push_back(new Controls(false, i));
			if(controls_[i] == 1)
				controllers[i]->set_inverted(true);
		}
		
}

Play_State_Base::~Play_State_Base()	 {
	for(int i = 0; i < 4; i++)	{
		delete controllers[i];
	}
}

void Play_State_Base::on_push()	{
		get_Window().mouse_hide(true);
		get_Window().mouse_grab(true);
		get_Video().set_clear_Color(Color(0,.1,.1,.1));
		get_Game().joy_mouse.enabled = false;
		Game_Model::get().start_up(genders, teams);
}

void Play_State_Base::on_pop()	{
		get_Window().mouse_hide(false);
		get_Window().mouse_grab(false);
		get_Video().set_clear_Color(m_prev_clear_color);
    get_Game().joy_mouse.enabled = true;
		Game_Model::get().finish();
}

void Play_State_Base::on_key(const SDL_KeyboardEvent &event) {
	controllers[0]->take_keyboard_input(event, 0);
	controllers[1]->take_keyboard_input(event, 1);
	Gamestate_Base::on_key(event); // Let Gamestate_Base handle it
} 

void Play_State_Base::on_mouse_motion(const SDL_MouseMotionEvent &event) {	
	int i = controllers[0]->get_cam_to_adjust();
	controllers[0]->reset_Cam();
	Game_Model::get().get_player(i)->adjust_pitch(event.yrel / 500.0f);
	Game_Model::get().get_player(i)->turn_left(-event.xrel / 500.0f);    
}

void Play_State_Base::on_joy_axis(const SDL_JoyAxisEvent &event)	{
	if(!controllers[event.which]->HandleJoy(event))
		Gamestate_Base::on_joy_axis(event);
}

void Play_State_Base::on_joy_hat(const SDL_JoyHatEvent &event)	{
	if(!controllers[event.which]->HandleJoy(event))
		Gamestate_Base::on_joy_hat(event);
}

void Play_State_Base::on_joy_button(const SDL_JoyButtonEvent &event)	{
	if(!controllers[event.which]->HandleJoy(event))	{
		Gamestate_Base::on_joy_button(event);
		get_Game().joy_mouse.enabled = false;
	}
}



void Play_State_Base::perform_logic()	
{
	for(int i = 0; i < 4; i++)	
		controllers[i]->adjust_Cam(Game_Model::get().get_player(i));

	for(int i = 0; i < 4; i++)
		controllers[i]->interact_with_player(Game_Model::get().get_player(i), Game_Model::get().get_time_step());
	

	//update player velocity/movement
	for(int i = 0; i < 4; i++)
		Game_Model::get().get_player(i)->calculate_movement(controllers[i]->give_movement());

	

	//updates all positions
	Game_Model::get().update();

	if (Game_Model::get().win())		
		get_Game().pop_state(); //Do something to win
}

void Play_State_Base::render()	{
	Game_Model::get().render();

	int width = get_Window().get_width();
	int height = get_Window().get_height();
//	get_Video().set_2d(pair<Point2f, Point2f>(Point2f(0,0), Point2f(width, height)));
//	get_Fonts()["system_36_800x600"].render_text(controllers[0]->give_stick_status().c_str(), Point2f(0, 0), Color(1, 0.1, 0.85, 0.1 ));
	if (Game_Model::get().table.get_collided())
		get_Fonts()["system_36_800x600"].render_text("Collision detected.", Point2f(0, 300), Color(1, 0.1, 0.85, 0.1 ));
}
