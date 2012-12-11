#pragma once

#include <zenilib.h>

using namespace std;
using namespace Zeni;

class End_Game_State : public Widget_Gamestate {
  End_Game_State(const End_Game_State &);
  End_Game_State operator=(const End_Game_State &);

public:
  End_Game_State()
    : Widget_Gamestate(make_pair(Point2f(0.0f, 0.0f), Point2f(800.0f, 600.0f)))
  {
	  cursor = 2;
	  confirm = false;
  }
  //~End_Game_State();

private:
	
	void render_controls(int y)
{

}
  void on_pop();

  void on_key(const SDL_KeyboardEvent &event);
  void on_joy_hat(const SDL_JoyHatEvent &event);
  void on_joy_button(const SDL_JoyButtonEvent &event);

  void perform_logic();
  void render();

  int cursor;
  bool confirm;
};