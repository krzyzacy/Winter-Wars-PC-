#include "Play_State_Base.h"

#include "Game_Model.h"

#include "Controls.h"
#include "View.h"
#include "Player.h"
#include "Player_View.h"
#include "Permanent.h"
#include "Team.h"
#include "End_Game_State.h"
#include "Utility.h"
#include "WWClient.h"
#include "Claim_Tree_Level.h"
#include "Tutorial_Level.h"

Play_State_Base::Play_State_Base(vector<Player_info*> *player_info_,
			bool isLocalGame_, bool isServer_, RakNet::SystemAddress server_addr)	:
	player_info(player_info_),
	m_prev_clear_color(get_Video().get_clear_Color()),	
	isLocal(isLocalGame_), isServer(isServer_), host_addr(server_addr)
{		
		set_pausable(false);
}

Play_State_Base::~Play_State_Base()	 {
}

void Play_State_Base::on_push()	{
		get_Window().mouse_hide(true);
		get_Window().mouse_grab(true);
		get_Video().set_clear_Color(Color(0,.1,.1,.1));
		get_Game().joy_mouse.enabled = false;

		Game_Model::get().change_level(new Tutorial_Level());
		Game_Model::get().start_up(*player_info);

		if(!isLocal)
			Game_Model::get().initialize_peer(isServer, host_addr);
				
		for(int i = 0; i < Game_Model::get().num_players() ; i++)	{
			controllers.push_back(new Controls(false, i));
			if(player_info->at(i)->controls_ == 1)
				controllers[i]->set_inverted(true);
		}
}

void Play_State_Base::on_pop()	{
	get_Window().mouse_hide(false);
	get_Window().mouse_grab(false);
	get_Video().set_clear_Color(m_prev_clear_color);
	get_Game().joy_mouse.enabled = true;
	Game_Model::get().finish();

	for (int i = 0 ; i < player_info->size() ; i++)
		delete player_info->at(i);
	delete player_info;

	for(int i = 0; i < controllers.size() ; i++)	{
		delete controllers[i];
	}
}

void Play_State_Base::on_key(const SDL_KeyboardEvent &event) {
	Controls::check_keyboard_player_change(event);

	if(Controls::Mouse_Camera == -1)
		Controls::take_God_keyboard(event);
	else	
		controllers[Controls::Mouse_Camera]->take_keyboard_input(event);

	Gamestate_Base::on_key(event); // Let Gamestate_Base handle it
} 

void Play_State_Base::on_mouse_button(const SDL_MouseButtonEvent &event)
{
	if(Controls::Mouse_Camera != -1)
		controllers[Controls::Mouse_Camera]->take_mouse_button_input(event);
}

void Play_State_Base::on_mouse_motion(const SDL_MouseMotionEvent &event) {	
	controllers[Controls::Mouse_Camera]->reset_Cam();
	Game_Model::get().get_player(Controls::Mouse_Camera)->adjust_pitch(event.yrel / 500.0f);
	Game_Model::get().get_player(Controls::Mouse_Camera)->turn_left(-event.xrel / 500.0f);    
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
	for(int i = 0; i < controllers.size(); i++)	
		controllers[i]->adjust_Cam(Game_Model::get().get_player(i));

	for(int i = 0; i < controllers.size(); i++)
		controllers[i]->interact_with_player(Game_Model::get().get_player(i), Game_Model::get().get_time_step());


	//update player velocity/movement
	for(int i = 0; i < controllers.size(); i++)
		Game_Model::get().get_player_here(i)->calculate_movement(controllers[i]->give_movement());



	//updates all positions
	Game_Model::get().update();

	if (Game_Model::get().win()){

		for(int i = 0; i < controllers.size(); i++)
			Joysticks::get().set_xinput_vibration(i, 0, 0);		

		get_Game().push_state(new End_Game_State());
	}



	// networking code here
	if(WWClient::isNetwork())
		WWClient::get()->WWhost_logic();
		//Game_Model::get().get_peer()->peer_logic();
}

void Play_State_Base::render()	{
	Game_Model::get().render();

	int width = get_Window().get_width();
	int height = get_Window().get_height();
//	get_Video().set_2d(pair<Point2f, Point2f>(Point2f(0,0), Point2f(width, height)));
//	get_Fonts()["system_36_800x600"].render_text(controllers[0]->give_stick_status().c_str(), Point2f(0, 0), Color(1, 0.1, 0.85, 0.1 ));
//	if (Game_Model::get().table.get_collided())
//		get_Fonts()["system_36_800x600"].render_text("Collision detected.", Point2f(0, 300), Color(1, 0.1, 0.85, 0.1 ));
}