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
#include <vector>
#include "Team.h"
#include "Object_factory.h"

#if defined(_DEBUG) && defined(_WINDOWS)
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

using namespace std;
using namespace Zeni;

  
class Instructions_State : public Widget_Gamestate {
  Instructions_State(const Instructions_State &);
  Instructions_State operator=(const Instructions_State &);

public:
  Instructions_State()
    : Widget_Gamestate(make_pair(Point2f(0.0f, 0.0f), Point2f(800.0f, 600.0f)))
  {
	  state = 0;
  }

private:
	
	void render_controls(int y)
{

}
  void on_key(const SDL_KeyboardEvent &event) {
    if(event.keysym.sym == SDLK_ESCAPE && event.state == SDL_PRESSED)
      get_Game().pop_state();
	if(event.keysym.sym == SDLK_RETURN && event.state == SDL_PRESSED){
			state ++;
		if(state == 3)
			get_Game().pop_state();
	}

  }

  void render() {
    Widget_Gamestate::render();

	get_Video().set_2d(make_pair(Point2f(0.0f, 0.0f), Point2f(1920.0f, 1200.0f)), true);
	if(state == 0){
		render_image("Instructions", Point2f(0.0f,0.0f), Point2f(1920.0f,1200.0f));
	}

	if(state == 1){
		render_image("Control_1", Point2f(0.0f,0.0f), Point2f(2048.0f,2048.0f));
	}
	if(state == 2){
		render_image("Control_2", Point2f(0.0f,0.0f), Point2f(2048.0f,2048.0f));
	}
  
	render_controls(0);
  }

  int state;
};

class Team_Select_State : public Widget_Gamestate {
    Team_Select_State(const Team_Select_State &);
    Team_Select_State operator=(const Team_Select_State &);
    
public:
    Team_Select_State()
    : Widget_Gamestate(make_pair(Point2f(0.0f, 0.0f), Point2f(960.0f, 600.0f)))
    {
		for(int player_idx = 0; player_idx < 4; player_idx++){
			player_state[player_idx] = 0;
			player_team_state[player_idx] = 0;
			player_gender_state[player_idx]  = 0;
			player_control_state[player_idx]  = 0;
			player_cursor[player_idx]  = 0;
			player_gender[player_idx]  = "Boy";
			player_team[player_idx]  = "Blue";
			player_control[player_idx]  = "Normal";
		}

		player_render_offset[0] = Point2f(0,0);
		player_render_offset[1] = Point2f(480,0);
		player_render_offset[2] = Point2f(0,300);
		player_render_offset[3] = Point2f(480,300);

		get_Game().joy_mouse.enabled = false;
		get_Window().mouse_hide(true);
		get_Window().mouse_grab(true);

		loading = false;
		start_game = 0.0f;
	

    }
    
private:
    void on_key(const SDL_KeyboardEvent &event) {
        if(event.keysym.sym == SDLK_ESCAPE && event.state == SDL_PRESSED){
            get_Game().pop_state();
        }
		else if(event.keysym.sym == SDLK_w && event.state == SDL_PRESSED){
			if(player_cursor[0] != 0)
				player_cursor[0] --;
		}
		else if(event.keysym.sym == SDLK_s && event.state == SDL_PRESSED){
			if(player_cursor[0] != 2)
				player_cursor[0] ++;
		}
		else if(event.keysym.sym == SDLK_a && event.state == SDL_PRESSED){
			if(player_cursor[0] == 0){
				player_gender_state[0] = (player_gender_state[0] + 1) % 2;
			}
			else if(player_cursor[event.which] == 2){
						player_control_state[event.which] = (player_control_state[event.which] + 1) % 2;
					}
			else{
				player_team_state[0] = (player_team_state[0] + 3) % 4;
			}
		}
		else if(event.keysym.sym == SDLK_d && event.state == SDL_PRESSED){
			if(player_cursor[0] == 0){
				player_gender_state[0] = (player_gender_state[0] + 1) % 2;
			}
			else if(player_cursor[event.which] == 2){
						player_control_state[event.which] = (player_control_state[event.which] + 1) % 2;
					}
			else{
				player_team_state[0] = (player_team_state[0] + 1) % 4;
			}
		}
        else if(event.keysym.sym == SDLK_RETURN && event.state == SDL_PRESSED){
			if(player_state[0] != 2)
				player_state[0] ++;
			else{
				loading = true;
			}
		}
    }

	void on_joy_hat(const SDL_JoyHatEvent &event) {
		
		if(player_state[event.which] == 1) {
			switch(event.value){
				case SDL_HAT_UP:    
					if(player_cursor[event.which] != 0)
						player_cursor[event.which] --;
					break;
			
				case SDL_HAT_LEFT:
					if(player_cursor[event.which] == 0){
						player_gender_state[event.which] = (player_gender_state[event.which] + 1) % 2;
					}
					else if(player_cursor[event.which] == 2){
						player_control_state[event.which] = (player_control_state[event.which] + 1) % 2;
					}
					else{
						player_team_state[event.which] = (player_team_state[event.which] + 3) % 4;
					}
					break;

				case SDL_HAT_RIGHT:
					if(player_cursor[event.which] == 0){
						player_gender_state[event.which] = (player_gender_state[event.which] + 1) % 2;
					}
					else if(player_cursor[event.which] == 2){
						player_control_state[event.which] = (player_control_state[event.which] + 1) % 2;
					}
					else{
						player_team_state[event.which] = (player_team_state[event.which] + 1) % 4;
					}
					break;
				case SDL_HAT_DOWN:
					if(player_cursor[event.which] != 2)
						player_cursor[event.which] ++ ;
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
						if(player_state[0] != 2)
							player_state[0] ++;
						else
							loading = true;
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

		if(start_game > 5.0f){

			for(int player_idx = 0; player_idx < 4; player_idx ++){
				genders_.push_back(player_gender[player_idx]);
				controls_.push_back(player_control_state[player_idx]);

				if(player_team[player_idx] == "Green"){
					colors_.push_back(0);
				}
				if(player_team[player_idx] == "Red"){
					colors_.push_back(1);
				}
				if(player_team[player_idx] == "Blue"){
					colors_.push_back(2);
				}
				if(player_team[player_idx] == "Orange"){
					colors_.push_back(3);
				}
			}

			//get_Game().pop_state();
			get_Game().push_state(new Play_State_Base(genders_, colors_, controls_));
		}


		for(int player_idx = 0; player_idx < 4; player_idx ++){
			if(player_gender_state[player_idx] == 0)
				player_gender[player_idx] = "Boy";
			else
				player_gender[player_idx] = "Girl";

			if(player_control_state[player_idx] == 0)
				player_control[player_idx] = "Normal";
			else
				player_control[player_idx] = "Inverted";

			if(player_team_state[player_idx] == 0)
				player_team[player_idx] = "Green";
			else if(player_team_state[player_idx] == 1)
				player_team[player_idx] = "Red";
			else if(player_team_state[player_idx] == 2)
				player_team[player_idx] = "Blue";
			else
				player_team[player_idx] = "Orange";
		}
	}

    void render() {
        Widget_Gamestate::render();

		render_image("ts1920", Point2f(0.0f,0.0f), Point2f(1024.0f,1024.0f));
		get_Fonts()["system_36_800x600"].render_text("Player 1" ,Point2f(270, 30), Color(0x99FF1111));
		get_Fonts()["system_36_800x600"].render_text("Player 2" ,Point2f(750, 30), Color(0x99FF1111));
		get_Fonts()["system_36_800x600"].render_text("Player 3" ,Point2f(270, 330), Color(0x99FF1111));
		get_Fonts()["system_36_800x600"].render_text("Player 4" ,Point2f(750, 330), Color(0x99FF1111));

		for(int player_idx = 0; player_idx < 4; player_idx ++){

			render_image("Wanted",Point2f(-40.0f + player_render_offset[player_idx].x, 0.0f + player_render_offset[player_idx].y), Point2f(290.0f + player_render_offset[player_idx].x, 330.0f + player_render_offset[player_idx].y));

			if(player_state[player_idx] != 0){
				render_image("Snowball",Point2f(235.0f + player_render_offset[player_idx].x, 67.0f + 42.0f * player_cursor[player_idx] + player_render_offset[player_idx].y), Point2f(265.0f + player_render_offset[player_idx].x, 97.0f + 40.0f * player_cursor[player_idx] + player_render_offset[player_idx].y));
				get_Fonts()["system_26_800x600"].render_text("Gender  >> " + player_gender[player_idx] ,Point2f(270 + player_render_offset[player_idx].x, 72 + player_render_offset[player_idx].y), Color(0x99FF1111));
				get_Fonts()["system_26_800x600"].render_text("Team    >> " + player_team[player_idx] ,Point2f(270 + player_render_offset[player_idx].x, 112 + player_render_offset[player_idx].y), Color(0x99FF1111));
				get_Fonts()["system_26_800x600"].render_text("Control >> " + player_control[player_idx] ,Point2f(270 + player_render_offset[player_idx].x, 152 + player_render_offset[player_idx].y), Color(0x99FF1111));
				render_image(player_gender[player_idx] + player_team[player_idx] + "Regular", Point2f(55 + player_render_offset[player_idx].x,125 + player_render_offset[player_idx].y),Point2f(188 + player_render_offset[player_idx].x,258 + player_render_offset[player_idx].y));
			}

			if(player_state[player_idx] >= 2){
				render_image("Ready",Point2f(100.0f + player_render_offset[player_idx].x, 70.0f + player_render_offset[player_idx].y), Point2f(430.0f + player_render_offset[player_idx].x, 400.0f + player_render_offset[player_idx].y));
			}
		}


		get_Fonts()["system_36_800x600"].render_text("Press Enter to continue" ,Point2f(600, 565), Color(0x99FF3333));

		if(loading){
			render_image("Loading", Point2f(0.0f,0.0f), Point2f(1024.0f,1024.0f));
			start_game += 1.0f;
		}
    }
    
	int player_state[4];
    int player_team_state[4];
	int player_gender_state[4];
	int player_control_state[4];
	int player_cursor[4];
	String player_gender[4];
	String player_team[4];
	String player_control[4];

	Point2f player_render_offset[4];
	bool loading;
	float start_game;

	vector<int> colors_;
	vector<Zeni::String> genders_;
	vector<int> controls_;
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
			render_image("ts800", Point2f(0.0f,0.0f), Point2f(1024.0f, 1024.0f));
			Title_State<Team_Select_State, Instructions_State>::render();
			//get_Video().set_2d(make_pair(Point2f(0.0f, 0.0f), Point2f(800.0f, 600.0f)), true);

			get_Fonts()["cat_110"].render_text("Winter Wars" ,Point2f(155, 60), Color(0xFF33BBE8));
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
