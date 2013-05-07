/*
	Winter Wars Team
	04/13/2013
*/

#include <zenilib.h>

#include "String.h"
#include <vector>


using namespace std;
using namespace Zeni;



class Global_Edit_State : public Widget_Gamestate {
  Global_Edit_State(const Global_Edit_State &);
  Global_Edit_State operator=(const Global_Edit_State &);

public:
  Global_Edit_State();

private:
  int cursor;
  int size;

  void render_controls(int y){}
  void on_pop(){
	  get_Game().joy_mouse.enabled = true;
  }
  void on_key(const SDL_KeyboardEvent &event);

  void on_joy_button(const SDL_JoyButtonEvent &event) {}

  void render();
};