#pragma once
//This class represents our standard gameplay. Everything neccessary will be in here
//If we want to add more modes later, then those classes can inherit from this one


#include <zenilib.h>
//This class basically replaces bootstrap (except for Instruction state stuff)
//I did not modify the relevant code, and I copy and pasted it here, but essentially 
//the play_state in bootstrap is disconnected

#include "Controls.h"
#include "View.h"
#include "Player.h"
#include "Player_View.h"
#include "Permanent.h"


using namespace std;
using namespace Zeni;



class Play_State_Base : public Gamestate_Base		{
  Play_State_Base(const Play_State_Base &);
  Play_State_Base operator=(const Play_State_Base &);
 
public:
	Play_State_Base();
	~Play_State_Base();


private:
  bool m_next;
  bool escape;

	//This will probably have to be modified to accomadate unknown player number
  Player Rend;
  Player Rend2;
  Player Rend3;
  Player Rend4;
  Permanent Perm;
  View view;

	//vector<Controls*> controllers;
	//For now  
	Controls test;

	Chronometer<Time> PlayTime;
  float time_passed;
	float time_step;
	Color m_prev_clear_color;

	void on_event(const SDL_Event &event);
//	void on_event(const Zeni_Input_ID &Zid, const float &confidence, const int &action);

	void on_joy_axis(const SDL_JoyAxisEvent &event);
  void on_joy_ball(const SDL_JoyBallEvent &event); 
  void on_joy_hat(const SDL_JoyHatEvent &event);
  void on_joy_button(const SDL_JoyButtonEvent &event);


	void on_push();
  void on_pop();

	void on_key(const SDL_KeyboardEvent &event);
  
	
	void on_mouse_motion(const SDL_MouseMotionEvent &event);

	void perform_logic();

	void render();

};


