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



class Play_State_Base : public Gamestate_II		{
  Play_State_Base(const Play_State_Base &);
  Play_State_Base operator=(const Play_State_Base &);
 
public:
  Play_State_Base() 
    : m_time_passed(0.0f)
	, m_next(false)
	, escape(false)
	, m_prev_clear_color(get_Video().get_clear_Color())
	, Perm(Point3f(30,10,0), Vector3f(2,2,2))
	,Rend(Point3f(1,0,20))
	,Rend2(Point3f(10,30,100))
	,Rend3(Point3f(0,0,50))
	,Rend4(Point3f(10,10,20))

  {
    set_pausable(true);
	view.add_renderable(&Rend);
	view.add_player_view(new Player_View(&Rend));
	view.add_renderable(&Rend2);
	view.add_player_view(new Player_View(&Rend2));
	view.add_renderable(&Rend3);
	view.add_player_view(new Player_View(&Rend3));
	view.add_renderable(&Rend4);
	view.add_player_view(new Player_View(&Rend4));
	view.add_renderable(&Perm);
  }

private:
  bool m_next;

  bool escape;
  Player Rend;
  Player Rend2;
  Player Rend3;
  Player Rend4;
  Permanent Perm;
  View view;


  vector<Controls*> controllers;

  
  Chronometer<Time> m_chrono;
  float m_time_passed;
	 Color m_prev_clear_color;
	
	void on_push() {
    get_Window().mouse_hide(true);
	get_Window().mouse_grab(true);
	m_chrono.start(); 
	
	get_Video().set_clear_Color(Color(0,.1,.1,.1));

  }

  void on_pop() {
    //get_Window().mouse_grab(false);
    get_Window().mouse_hide(false);
  get_Window().mouse_grab(false);
	get_Video().set_clear_Color(m_prev_clear_color);
    //get_Game().joy_mouse.enabled = true;
  }


	void on_key(const SDL_KeyboardEvent &event) {
		switch(event.keysym.sym) {
		
		  default:
			Gamestate_II::on_key(event); // Let Gamestate_II handle it
			break;
		}
	} 
	 
  void on_mouse_motion(const SDL_MouseMotionEvent &event) {
    Rend.adjust_pitch(event.yrel / 500.0f);
    Rend.turn_left(-event.xrel / 500.0f);    

	Rend2.adjust_pitch(event.yrel / 500.0f);
    Rend2.turn_left(-event.xrel / 500.0f);   

	Rend3.adjust_pitch(event.yrel / 500.0f);
    Rend3.turn_left(-event.xrel / 500.0f);  

	Rend4.adjust_pitch(event.yrel / 500.0f);
    Rend4.turn_left(-event.xrel / 500.0f);
  }


	void perform_logic()
	{

	}

	void render()
	{
		Video &vr = get_Video();		
		view.render();

	}

};



