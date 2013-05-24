/* This file is part of the Zenipex Library (zenilib).
 * Copyleft (C) 2011 Mitchell Keith Bloch (bazald).
 *
 * This source file is simply under the public domain.
 */


/*
	Winter Wars Team
	04/13/2013
*/

#include <zenilib.h>

#include "String.h"
#include <vector>
#include "Credits_State.h"
#include "Instructions_State.h"
#include "Mode_State.h"


#if defined(_DEBUG) && defined(_WINDOWS)
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

using namespace std;
using namespace Zeni;


class Title_State_Custom : public Title_State<Modes_State, Play_State_Base, Instructions_State, Credits_State>{

	public:
		Title_State_Custom()
		: Title_State<Modes_State, Play_State_Base, Instructions_State, Credits_State>("")
		{
			m_widgets.unlend_Widget(title);
			get_Sound().set_BGM("sfx/HappyTreeFriends");
			get_Sound().set_BGM_looping(1);
			get_Sound().play_BGM();
		}

		void on_push(){
			get_Window().mouse_hide(false);
		}

		void on_uncover()	{
			get_Window().mouse_hide(false);
			get_Window().mouse_grab(false);
			get_Game().joy_mouse.enabled = true;
		}

		void render() {
			int width = get_Window().get_width();
			int height = get_Window().get_height();

			render_image("ts800", Point2f(0.0f,0.0f), Point2f(1024.0f, 1024.0f));
			Title_State<Modes_State, Play_State_Base, Instructions_State, Credits_State>::render();
			//get_Video().set_2d(make_pair(Point2f(0.0f, 0.0f), Point2f(800.0f, 600.0f)), true);

			//get_Fonts()["cat_110"].render_text("Winter Wars" ,Point2f(155, 60), Color(0xFF33BBE8));
			get_Fonts()["cat"].render_text("Winter Wars", Point3f(155, 60, 0), Vector3f(1,0,0), Vector3f(0,1,0),Color(0xFF33BBE8));
		}
};

class Bootstrap {
  class Gamestate_One_Initializer : public Gamestate_Zero_Initializer {
    virtual Gamestate_Base * operator()() {
	  //Useful if want to lock resolution(windowed)
	  //Window::preinit_resizable(false);
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
