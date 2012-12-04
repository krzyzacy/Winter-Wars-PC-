/* This file is part of the Zenipex Library (zenilib).
 * Copyleft (C) 2011 Mitchell Keith Bloch (bazald).
 *
 * This source file is simply under the public domain.
 */

#include <zenilib.h>

#include "Controls.h"
#include "View.h"
#include "Player.h"
#include "Player_View.h"
#include "Permanent.h"


#include "Play_State_Base.h"

#include "String.h"

#if defined(_DEBUG) && defined(_WINDOWS)
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

using namespace std;
using namespace Zeni;


//
//class Play_State : public Gamestate_Base {
//  Play_State(const Play_State &);
//  Play_State operator=(const Play_State &);
// 
//public:
//  Play_State() 
//    : m_time_passed(0.0f)
//	, m_next(false)
//	, escape(false)
//	, m_prev_clear_color(get_Video().get_clear_Color())
//	, Perm(Point3f(30,10,0), Vector3f(2,2,2))
//	,Rend(Point3f(1,0,20))
//	,Rend2(Point3f(10,30,100))
//	,Rend3(Point3f(0,0,50))
//	,Rend4(Point3f(10,10,20))
//
//  {
//    set_pausable(true);
//	view.add_renderable(&Rend);
//	view.add_player_view(new Player_View(&Rend));
//	view.add_renderable(&Rend2);
//	view.add_player_view(new Player_View(&Rend2));
//	view.add_renderable(&Rend3);
//	view.add_player_view(new Player_View(&Rend3));
//	view.add_renderable(&Rend4);
//	view.add_player_view(new Player_View(&Rend4));
//	view.add_renderable(&Perm);
//  }
//
//private:
//  bool m_next;
//
//  bool escape;
//  Player Rend;
//  Player Rend2;
//  Player Rend3;
//  Player Rend4;
//  Permanent Perm;
//  View view;
//
//
//  vector<Controls*> controllers;
//
//  
//  Chronometer<Time> m_chrono;
//  float m_time_passed;
//	 Color m_prev_clear_color;
//	
//	void on_push() {
//    //get_Window().mouse_grab(true);
//    get_Window().mouse_hide(true);
//	get_Window().mouse_grab(true);
//	m_chrono.start(); 
//	
////	Game_Model::get().restart(Players, difficulty);
//
//	get_Video().set_clear_Color(Color(0,.1,.1,.1));
//
//    //get_Game().joy_mouse.enabled = false;
//  }
//
//  void on_pop() {
//    //get_Window().mouse_grab(false);
//    get_Window().mouse_hide(false);
//  get_Window().mouse_grab(false);
//	get_Video().set_clear_Color(m_prev_clear_color);
//    //get_Game().joy_mouse.enabled = true;
//  }/*
//  void on_mouse_button(const SDL_MouseButtonEvent &event) {
//	  switch(event.button)
//	  {
//	  case SDL_BUTTON_LEFT:
//		      Game_Model::get().get_player(0)->m_controls.pack = event.state == SDL_PRESSED;
//			  Game_Model::get().get_player(0)->m_controls.finish_pack = event.state == SDL_RELEASED;
//			  break;
//	  }
//  }*/
//	 void on_key(const SDL_KeyboardEvent &event) {
//		switch(event.keysym.sym) {
//		
//		  default:
//			Gamestate_Base::on_key(event); // Let Gamestate_Base handle it
//			break;
//		}
//	} 
//	 
//  void on_mouse_motion(const SDL_MouseMotionEvent &event) {
//    Rend.adjust_pitch(event.yrel / 500.0f);
//    Rend.turn_left(-event.xrel / 500.0f);    
//
//	Rend2.adjust_pitch(event.yrel / 500.0f);
//    Rend2.turn_left(-event.xrel / 500.0f);   
//
//	Rend3.adjust_pitch(event.yrel / 500.0f);
//    Rend3.turn_left(-event.xrel / 500.0f);  
//
//	Rend4.adjust_pitch(event.yrel / 500.0f);
//    Rend4.turn_left(-event.xrel / 500.0f);
//  }
//
//
//	void perform_logic()
//	{
//
//	}
//
//	void render()
//	{
//		Video &vr = get_Video();
//		
//
//		
//		view.render();
//
//	}
//};
//
//
//
//class Play_State_Top : public Widget_Gamestate {
//public:
//	Play_State_Top()
//    : Widget_Gamestate(std::make_pair(Point2f(0.0f, 0.0f), Point2f(800.0f, 600.0f)), true)
//  {	
////	 m_widgets.lend_Widget(p2); 
////	 m_widgets.lend_Widget(p1);    
////	 m_widgets.lend_Widget(l1);    
////	 m_widgets.lend_Widget(l2);    
////	 m_widgets.lend_Widget(l3);     
////	 m_widgets.lend_Widget(l4);    
////	 m_widgets.lend_Widget(l5);    
////	 m_widgets.lend_Widget(l6); 
////	 m_widgets.lend_Widget(pop_button);
//	}
///*
//class P1_Button : public Text_Button
//{
//public:
//    P1_Button()
//      : Text_Button(Point2f(50.0f, 50.0f)
//		  , Point2f(250.0f, 100.0f)
//		  , "system_36_800x600", "1 Player")
//	{}
//	  
//	void on_accept() {
//		Players = 1;
//		screen_x_c = 512;
//		get_Game().push_state(new Play_State);
//    }
//} p1;
//*/
//	/*
//
//class P2_Button : public Text_Button
//{
//public:
//    P2_Button()
//      : Text_Button(Point2f(300, 500.0f)
//		  , Point2f(500, 550.0f)
//		  , "system_36_800x600", "2 Player Wind"){}
//	  
//	void on_accept() {
//		Players = 2;
//		difficulty = 6;
//		screen_x_c = 512+300;
//		Game_Model::get().score_needed = 20000;
//		get_Game().push_state(new Play_State);
//	}
//
//} p2;
//*//*
//class Level_1 : public Text_Button
//{
//public:
//    Level_1()
//      : Text_Button(Point2f(300.0f, 50.0f)
//		  , Point2f(500.0f, 100.0f)
//		  , "system_36_800x600", "Level 1")
//	{this->color = Color(1,0,0,1);}
//	  
//	void on_accept() {
//		Players = 1;
//		difficulty = 1;
//		get_Game().push_state(new Play_State);
//    }
//} l1;
//
//class Level_2 : public Text_Button
//{
//public:
//    Level_2()
//      : Text_Button(Point2f(300.0f, 125.0f)
//		  , Point2f(500.0f, 175.0f)
//		  , "system_36_800x600", "Level 2")
//	{this->color = Color(1,0,1,1);}
//	  
//	void on_accept() {
//		Players = 1;
//		difficulty = 2;
//		get_Game().push_state(new Play_State);
//    }
//} l2;
//
//class Level_3 : public Text_Button
//{
//public:
//    Level_3()
//      : Text_Button(Point2f(300.0f, 200.0f)
//		  , Point2f(500.0f, 250.0f)
//		  , "system_36_800x600", "Level 3")
//	{this->color = Color(1,0,1,0);}
//	  
//	void on_accept() {
//		Players = 1;
//		difficulty = 3;
//		get_Game().push_state(new Play_State);
//    }
//} l3;
///*
//class Level_4 : public Text_Button
//{
//public:
//    Level_4()
//      : Text_Button(Point2f(300.0f, 275.0f)
//		  , Point2f(500.0f, 325.0f)
//		  , "system_36_800x600", "Level 4")
//	{this->color = Color(1,0,1,1);}
//	  
//	void on_accept() {
//		difficulty = 4;
//		Players = 1;
//		screen_x_c = 512+50;
//		Game_Model::get().score_needed = 10000;
//		get_Game().push_state(new Play_State);
//    }
//} l4;
//
//class Level_5 : public Text_Button
//{
//public:
//    Level_5()
//      : Text_Button(Point2f(300.0f, 350.0f)
//		  , Point2f(500.0f, 400.0f)
//		  , "system_36_800x600", "Level 5")
//	{this->color = Color(1,0,1,1);}
//	  
//	void on_accept() {
//		difficulty = 5;
//		Players = 1;
//		screen_x_c = 512+50;
//		Game_Model::get().score_needed = 15000;
//		get_Game().push_state(new Play_State);
//    }
//} l5;
//
//class Level_6 : public Text_Button
//{
//public:
//    Level_6()
//      : Text_Button(Point2f(300.0f, 425.0f)
//		  , Point2f(500.0f, 475.0f)
//		  , "system_36_800x600", "Level 6 - Wind")
//	{this->color = Color(1,0,1,1);}
//	  
//	void on_accept() {
//		Players = 1;
//		difficulty = 6;
//		screen_x_c = 512+100;
//		Game_Model::get().score_needed = 20000;
//		get_Game().push_state(new Play_State);
//    }
//} l6;
//
//*//*
// class Pop_Button : public Text_Button {
//	  public:
//    Pop_Button()
//      : Text_Button(Point2f(600, 550.0f), Point2f(800, 600.0f), "system_36_800x600", "Main Menu")
//    {
//    }
//	 void on_accept() {
//      get_Game().pop_state();
//    }
//
//  } pop_button;
//
//  
//  */
//  };
//

  
class Instructions_State : public Widget_Gamestate {
  Instructions_State(const Instructions_State &);
  Instructions_State operator=(const Instructions_State &);

public:
  Instructions_State()
    : Widget_Gamestate(make_pair(Point2f(0.0f, 0.0f), Point2f(800.0f, 600.0f)))
  {
  }

private:
	
	void render_controls(int y)
{

}
  void on_key(const SDL_KeyboardEvent &event) {
    if(event.keysym.sym == SDLK_ESCAPE && event.state == SDL_PRESSED)
      get_Game().pop_state();
  }

  void render() {
    Widget_Gamestate::render();

  
	render_controls(0);
  }
};

class Team_Select_State : public Widget_Gamestate {
    Team_Select_State(const Team_Select_State &);
    Team_Select_State operator=(const Team_Select_State &);
    
public:
    Team_Select_State()
    : Widget_Gamestate(make_pair(Point2f(0.0f, 0.0f), Point2f(960.0f, 600.0f)))
    {
		for(int player_idx = 0; player_idx < 4; player_idx ++){
			player_state[player_idx] = 0;
			player_team_state[player_idx] = 0;
			player_gender_state[player_idx]  = 0;
			player_cursor[player_idx]  = 0;
			player_gender[player_idx]  = "Boy";
			player_team[player_idx]  = "Blue";
		}

		player_render_offset[0] = Point2f(0,0);
		player_render_offset[1] = Point2f(480,0);
		player_render_offset[2] = Point2f(0,300);
		player_render_offset[3] = Point2f(480,300);

		get_Game().joy_mouse.enabled = false;
		get_Window().mouse_hide(true);
		get_Window().mouse_grab(true);

    }
    
private:
    void on_key(const SDL_KeyboardEvent &event) {
        if(event.keysym.sym == SDLK_ESCAPE && event.state == SDL_PRESSED){
            get_Game().pop_state();
        }
        else if(event.keysym.sym == SDLK_RETURN && event.state == SDL_PRESSED){
			if(player_state[0] != 3)
				player_state[0] ++;
			else{
				get_Game().pop_state();
				get_Game().push_state(new Play_State_Base());
			}
		}
    }

	void on_joy_hat(const SDL_JoyHatEvent &event) {
		
		if(player_state[event.which] == 1) {
			switch(event.value){
				case SDL_HAT_UP:    
					if(player_cursor[event.which] == 1)
						player_cursor[event.which] = 0;
					break;
			
				case SDL_HAT_LEFT:
					if(player_cursor[event.which] == 0){
						player_gender_state[event.which] = (player_gender_state[event.which] + 1) % 2;
					}
					else{
						player_team_state[event.which] = (player_team_state[event.which] + 3) % 4;
					}
					break;

				case SDL_HAT_RIGHT:
					if(player_cursor[event.which] == 0){
						player_gender_state[event.which] = (player_gender_state[event.which] + 1) % 2;
					}
					else{
						player_team_state[event.which] = (player_team_state[event.which] + 1) % 4;
					}
					break;
				case SDL_HAT_DOWN:
					if(player_cursor[event.which] == 0)
						player_cursor[event.which] = 1;
					break;
				//case SDL_HAT_RIGHTDOWN:
				default:
					break;
			}
		}

	}

	void on_joy_button(const SDL_JoyButtonEvent &event){
		if(event.which == 0){ // player_1
			switch(event.button){
				case 0: // A
					if(event.state == SDL_PRESSED)	{
						if(player_state[0] != 3)
							player_state[0] ++;
						else{
							get_Game().pop_state();
							get_Game().push_state(new Play_State_Base());
						}
					}
					break;
				case 1: // B
					if(event.state == SDL_PRESSED)	{
						if(player_state[0] != 0)
						player_state[0] --;
					}
					break;
				default:
					break;
			}
		}
		else{ // player_2 - 4
			switch(event.button){
				case 0: // A
					if(event.state == SDL_PRESSED)	{
						if(player_state[event.which] != 2)
							player_state[event.which] ++;
					}
					break;
				case 1: // B
					if(event.state == SDL_PRESSED)	{
						if(player_state[event.which] != 0)
							player_state[event.which] --;
					}
					break;
				default:
					break;
			}
		}
	}
    
	void perform_logic(){

		for(int player_idx = 0; player_idx < 4; player_idx ++){
			if(player_gender_state[player_idx] == 0)
				player_gender[player_idx] = "Boy";
			else
				player_gender[player_idx] = "Girl";

			if(player_team_state[player_idx] == 0)
				player_team[player_idx] = "Blue";
			else if(player_team_state[player_idx] == 1)
				player_team[player_idx] = "Green";
			else if(player_team_state[player_idx] == 2)
				player_team[player_idx] = "Red";
			else
				player_team[player_idx] = "Purple";
		}
	}

    void render() {
        Widget_Gamestate::render();
        
		render_image("Teamselect", Point2f(0.0f,0.0f), Point2f(1024.0f,1024.0f));
		get_Fonts()["system_36_800x600"].render_text("Player 1" ,Point2f(270, 30), Color(0x99FF1111));
		get_Fonts()["system_36_800x600"].render_text("Player 2" ,Point2f(750, 30), Color(0x99FF1111));
		get_Fonts()["system_36_800x600"].render_text("Player 3" ,Point2f(270, 330), Color(0x99FF1111));
		get_Fonts()["system_36_800x600"].render_text("Player 4" ,Point2f(750, 330), Color(0x99FF1111));



		for(int player_idx = 0; player_idx < 4; player_idx ++){

			render_image("Wanted",Point2f(-40.0f + player_render_offset[player_idx].x, 0.0f + player_render_offset[player_idx].y), Point2f(290.0f + player_render_offset[player_idx].x, 330.0f + player_render_offset[player_idx].y));

			if(player_state[player_idx] != 0){
				render_image("Snowball",Point2f(235.0f + player_render_offset[player_idx].x, 67.0f + 42.0f * player_cursor[player_idx] + player_render_offset[player_idx].y), Point2f(265.0f + player_render_offset[player_idx].x, 97.0f + 40.0f * player_cursor[player_idx] + player_render_offset[player_idx].y));
				get_Fonts()["system_26_800x600"].render_text("Gender: -> " + player_gender[player_idx] ,Point2f(270 + player_render_offset[player_idx].x, 72 + player_render_offset[player_idx].y), Color(0x99FF1111));
				get_Fonts()["system_26_800x600"].render_text("Team: -> " + player_team[player_idx] ,Point2f(270 + player_render_offset[player_idx].x, 112 + player_render_offset[player_idx].y), Color(0x99FF1111));
				render_image(player_gender[player_idx] + player_team[player_idx] + "Regular", Point2f(55 + player_render_offset[player_idx].x,125 + player_render_offset[player_idx].y),Point2f(188 + player_render_offset[player_idx].x,258 + player_render_offset[player_idx].y));
			}

			if(player_state[player_idx] >= 2){
				get_Fonts()["system_36_800x600"].render_text(" READY! " ,Point2f(270 + player_render_offset[player_idx].x, 170 + player_render_offset[player_idx].y), Color(0x99FF0000));
			}
		}


		get_Fonts()["system_36_800x600"].render_text("Press Enter to continue" ,Point2f(600, 565), Color(0x99FF3333));
    }
    
	int player_state[4];
    int player_team_state[4];
	int player_gender_state[4];
	int player_cursor[4];
	String player_gender[4];
	String player_team[4];

	Point2f player_render_offset[4];
	//Point2f player_render_base;
};

class Title_State_Custom : public Title_State<Team_Select_State, Instructions_State>{

	public:
		Title_State_Custom()
		: Title_State<Team_Select_State, Instructions_State>("")
		{
			m_widgets.unlend_Widget(title);
		}

		void render() {
			Title_State<Team_Select_State, Instructions_State>::render();
			//get_Video().set_2d(make_pair(Point2f(0.0f, 0.0f), Point2f(960.0f, 600.0f)), true);

			render_image("Titlescreen", Point2f(0.0f,0.0f), Point2f(1024.0f,1024.0f));
		}
};

class Bootstrap {
  class Gamestate_One_Initializer : public Gamestate_Zero_Initializer {
    virtual Gamestate_Base * operator()() {
      Window::set_title("Winter Wars");

      get_Joysticks();
      get_Video();
      get_Textures();
      get_Fonts();
      get_Sounds();
      get_Game().joy_mouse.enabled = true;

	  return new Title_State_Custom();
	  //Old state
    //return new Title_State<Play_State, Instructions_State>("Winter Wars\n");
	  //return new Title_State<Play_State_Base, Instructions_State>("Winter Wars\n");
    }
  } m_goi;

public:
  Bootstrap() {
    g_gzi = &m_goi;
  }
} g_bootstrap;

int main(int argc, char **argv) {
  return zenilib_main(argc, argv);
}
