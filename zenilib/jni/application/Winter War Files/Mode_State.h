/*
	Winter Wars Team
	04/13/2013
*/

#include <zenilib.h>

#include "String.h"
#include <vector>
#include "Lobby_State.h"
#include "Team_Select_State.h"

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
	  get_Game().joy_mouse.enabled = true;
  }

private:
  int state;
  void render_controls(int y){}
  void on_pop(){
	  get_Game().joy_mouse.enabled = true;
  }
  void on_key(const SDL_KeyboardEvent &event) {
    if(event.keysym.sym == SDLK_ESCAPE && event.state == SDL_PRESSED)
      get_Game().pop_state();
	if(event.keysym.sym == SDLK_a && event.state == SDL_PRESSED)
      get_Game().push_state(new Team_Select_State());
	if(event.keysym.sym == SDLK_b && event.state == SDL_PRESSED)
      get_Game().push_state(new Lobby_State());
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

  void render() {
    Widget_Gamestate::render();
	get_Fonts()["system_36_800x600"].render_text("About:Blank" ,Point2f(155, 60), Color(0xFF33BBE8));
	get_Fonts()["system_36_800x600"].render_text("A for local game" ,Point2f(100, 180), Color(0xFF33BBE8));
	get_Fonts()["system_36_800x600"].render_text("B for network game" ,Point2f(100, 250), Color(0xFF33BBE8));
	//get_Video().set_2d(make_pair(Point2f(0.0f, 0.0f), Point2f(1920.0f, 1200.0f)), true);
	//render_image("ts800", Point2f(0.0f,0.0f), Point2f(1024.0f, 1024.0f));
	render_controls(0);
  }
};