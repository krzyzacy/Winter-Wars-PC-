/*
	Winter Wars Team
	04/13/2013
*/

#include <zenilib.h>

#include "String.h"
#include <vector>
#include "Lobby_State.h"
#include "Team_Select_State.h"
#include "Global_Edit_State.h"

using namespace std;
using namespace Zeni;



class Modes_State : public Widget_Gamestate {
  Modes_State(const Modes_State &);
  Modes_State operator=(const Modes_State &);

public:
  Modes_State()
    : Widget_Gamestate(make_pair(Point2f(0.0f, 0.0f), Point2f(800.0f, 600.0f)))
  {
	  state = 0;
	  state_num = 4;
	  get_Game().joy_mouse.enabled = true;

	  hovered = Zeni::Color(0xFFFF0000);
	  unhovered = Zeni::Color(0xFF33BBE8);

	  buttom_msg.push_back("> Claim Tree Level");
	  buttom_msg.push_back("> Snowball Fight");
	  buttom_msg.push_back("> Network Game");
	  buttom_msg.push_back("> Change Globals");

	  for(int i = 0; i < state_num; i++){
		buttom_clr.push_back(unhovered);
	  }
  }

private:
  int state;
  int state_num;
  float mouse_x;
  float mouse_y;
  Zeni::Color hovered;
  Zeni::Color unhovered;
  vector<Zeni::String> buttom_msg;
  vector<Zeni::Color> buttom_clr;

  void render_controls(int y){}
  void on_pop(){
	  get_Game().joy_mouse.enabled = true;
  }
  void on_key(const SDL_KeyboardEvent &event) {
    if(event.keysym.sym == SDLK_ESCAPE && event.state == SDL_PRESSED)
      get_Game().pop_state();
  }

  void on_joy_button(const SDL_JoyButtonEvent &event) {
		switch(event.button){
			case 0: // A
				break;

			case 1: // B
				break;
				
			default:
				break;
		}
	}

	void on_uncover()	{
		get_Window().mouse_hide(false);
		get_Window().mouse_grab(false);
		get_Game().joy_mouse.enabled = true;
	}

	void on_cover()	{
		get_Window().mouse_hide(true);
		get_Window().mouse_grab(true);
		get_Game().joy_mouse.enabled = false;
	}
  
  void on_mouse_motion(const SDL_MouseMotionEvent &event){

	  float ratio_width = get_Window().get_width() / 800.0f;
	  float ratio_height = get_Window().get_height() / 600.0f;

	  mouse_x = event.x / ratio_width;
	  mouse_y = event.y / ratio_height;

	  int hover_idx = -1;

	  if(mouse_x > 100 && mouse_x < 450){
		  if(mouse_y > 160 && mouse_y < 230){
			  hover_idx = 0;
		  }
		  else if(mouse_y > 230 && mouse_y < 300){
			  hover_idx = 1;
		  }
		  else if(mouse_y > 300 && mouse_y < 370){
			  hover_idx = 2;
		  }
		  else if(mouse_y > 370 && mouse_y < 440){
			  hover_idx = 3;
		  }
		  else{
			  hover_idx = -1;
		  }
	  }
	  else{
		  hover_idx = -1;
	  }

	  for(int i = 0; i < state_num; i++){
		  if(i == hover_idx){
			  buttom_clr[i] = hovered;
		  }
		  else{
			  buttom_clr[i] = unhovered;
		  }
	  }
  }

  void on_mouse_button(const SDL_MouseButtonEvent &event){

	  if(mouse_x > 100 && mouse_x < 700){
		  if(mouse_y > 180 && mouse_y < 250){
			  get_Game().push_state(new Team_Select_State("Claim Tree"));
		  }
		  else if(mouse_y > 250 && mouse_y < 320){
			  get_Game().push_state(new Team_Select_State("Death Match"));
		  }
		  else if(mouse_y > 320 && mouse_y < 390){
			  get_Game().push_state(new Lobby_State());
		  }
		  else if(mouse_y > 390 && mouse_y < 460){
			  get_Game().push_state(new Global_Edit_State());
		  }
	  }
  }

  void render() {
    Widget_Gamestate::render();
	//get_Fonts()["system_36_800x600"].render_text("Mouse.x : " + itoa(mouse_x) + " & Mouse.y : " + itoa(mouse_y) ,Point2f(155, 10), Color(0xFF33BBE8));
	get_Fonts()["system_36_800x600"].render_text("Select Game Mode: " ,Point2f(155, 60), Color(0xFF33BBE8));

	for(int i = 0; i < state_num; i++){
		get_Fonts()["system_36_800x600"].render_text(buttom_msg[i] ,Point2f(100, 180 + i * 70), buttom_clr[i]);
	}

	//get_Video().set_2d(make_pair(Point2f(0.0f, 0.0f), Point2f(1920.0f, 1200.0f)), true);
	//render_image("ts800", Point2f(0.0f,0.0f), Point2f(1024.0f, 1024.0f));
	render_controls(0);
  }
};
