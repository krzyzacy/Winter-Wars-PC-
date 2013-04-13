/*
	Winter Wars Team
	04/13/2013
*/

#include <zenilib.h>

#include "String.h"
#include <vector>

using namespace std;
using namespace Zeni;

class Credits_State : public Widget_Gamestate {
  Credits_State(const Credits_State &);
  Credits_State operator=(const Credits_State &);

public:
  Credits_State()
    : Widget_Gamestate(make_pair(Point2f(0.0f, 0.0f), Point2f(800.0f, 600.0f)))
  {
	  state = 0;
	  get_Game().joy_mouse.enabled = false;
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
			if(state == 1)
				get_Game().pop_state();
	}
  }

  void on_joy_button(const SDL_JoyButtonEvent &event) {
	//if(event.which == 0){
		switch(event.button){
			case 0: // A
				if(event.state == SDL_PRESSED)	{
					state ++;
					if(state == 1)
						get_Game().pop_state();
				}
				break;

			case 1: // B
				get_Game().pop_state();
				break;
				
			default:
				break;
		}
	}

  void render() {
    Widget_Gamestate::render();

	get_Video().set_2d(make_pair(Point2f(0.0f, 0.0f), Point2f(1920.0f, 1200.0f)), true);
	if(state == 0){
		render_image("credits", Point2f(0.0f,0.0f), Point2f(2048.0f,2048.0f));
	}
  
	render_controls(0);
  }

  int state;
};