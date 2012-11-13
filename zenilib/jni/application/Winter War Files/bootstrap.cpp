/* This file is part of the Zenipex Library (zenilib).
 * Copyleft (C) 2011 Mitchell Keith Bloch (bazald).
 *
 * This source file is simply under the public domain.
 */

#include <zenilib.h>

#if defined(_DEBUG) && defined(_WINDOWS)
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

using namespace std;
using namespace Zeni;

class Play_State : public Gamestate_Base {
  Play_State(const Play_State &);
  Play_State operator=(const Play_State &);
 
public:
  Play_State() 
    : m_time_passed(0.0f)
	, m_next(false)
	, escape(false)
	, m_prev_clear_color(get_Video().get_clear_Color())
  {
    set_pausable(true);
  }

private:
  bool m_next;

  bool escape;


  vector<Controls*> controllers;

  
  Chronometer<Time> m_chrono;
  float m_time_passed;
	 Color m_prev_clear_color;
	
	void on_push() {
    //get_Window().mouse_grab(true);
    get_Window().mouse_hide(true);
	get_Window().mouse_grab(true);
	m_chrono.start(); 
	
//	Game_Model::get().restart(Players, difficulty);

	get_Video().set_clear_Color(Color(0,.1,.1,.1));

    //get_Game().joy_mouse.enabled = false;
  }

  void on_pop() {
    //get_Window().mouse_grab(false);
    get_Window().mouse_hide(false);
  get_Window().mouse_grab(false);
	get_Video().set_clear_Color(m_prev_clear_color);
    //get_Game().joy_mouse.enabled = true;
  }/*
  void on_mouse_button(const SDL_MouseButtonEvent &event) {
	  switch(event.button)
	  {
	  case SDL_BUTTON_LEFT:
		      Game_Model::get().get_player(0)->m_controls.pack = event.state == SDL_PRESSED;
			  Game_Model::get().get_player(0)->m_controls.finish_pack = event.state == SDL_RELEASED;
			  break;
	  }
  }*/
	 void on_key(const SDL_KeyboardEvent &event) {
		switch(event.keysym.sym) {
		/*  case SDLK_w:
			Game_Model::get().get_player(0)->m_controls.forward = event.type == SDL_KEYDOWN;
			break;

		  case SDLK_a:
			Game_Model::get().get_player(0)->m_controls.left = event.type == SDL_KEYDOWN;
			break;

		  case SDLK_s:
			Game_Model::get().get_player(0)->m_controls.back = event.type == SDL_KEYDOWN;
			break;

		  case SDLK_d:
			Game_Model::get().get_player(0)->m_controls.right = event.type == SDL_KEYDOWN;
			break;
  
		  case SDLK_RETURN:
			  m_next = event.type == SDL_KEYDOWN;
			  break;

		  case SDLK_q:
			  Game_Model::get().get_player(0)->m_controls.pack = event.type == SDL_KEYDOWN;
			  Game_Model::get().get_player(0)->m_controls.finish_pack = event.type == SDL_KEYUP;
			  break;

		  case SDLK_SPACE:
			  Game_Model::get().get_player(0)->m_controls.throw_ball = event.type == SDL_KEYDOWN;
			  break;

		  case SDLK_ESCAPE:
			  escape = event.type == SDL_KEYDOWN;
			  if (Game_Model::get().game_over())
				  break;
			  */
		  default:
			Gamestate_Base::on_key(event); // Let Gamestate_Base handle it
			break;
		}
	} 
	 
  void on_mouse_motion(const SDL_MouseMotionEvent &event) {/*
    Game_Model::get().get_player(0)->adjust_pitch(event.yrel / 500.0f);
    Game_Model::get().get_player(0)->turn_left_xy(-event.xrel / 500.0f);*/
  }


	void perform_logic()
	{

	}

	void render()
	{
		Video &vr = get_Video();
		
		
		/*
		vr.set_3d(Game_Model::get().get_player(0)->m_camera);
	
		if (Game_Model::get().game_over())
		{	

		}*/
	}
};



class Play_State_Top : public Widget_Gamestate {
public:
	Play_State_Top()
    : Widget_Gamestate(std::make_pair(Point2f(0.0f, 0.0f), Point2f(800.0f, 600.0f)), true)
  {	
//	 m_widgets.lend_Widget(p2); 
//	 m_widgets.lend_Widget(p1);    
//	 m_widgets.lend_Widget(l1);    
//	 m_widgets.lend_Widget(l2);    
//	 m_widgets.lend_Widget(l3);     
//	 m_widgets.lend_Widget(l4);    
//	 m_widgets.lend_Widget(l5);    
//	 m_widgets.lend_Widget(l6); 
//	 m_widgets.lend_Widget(pop_button);
	}
/*
class P1_Button : public Text_Button
{
public:
    P1_Button()
      : Text_Button(Point2f(50.0f, 50.0f)
		  , Point2f(250.0f, 100.0f)
		  , "system_36_800x600", "1 Player")
	{}
	  
	void on_accept() {
		Players = 1;
		screen_x_c = 512;
		get_Game().push_state(new Play_State);
    }
} p1;
*/
	/*

class P2_Button : public Text_Button
{
public:
    P2_Button()
      : Text_Button(Point2f(300, 500.0f)
		  , Point2f(500, 550.0f)
		  , "system_36_800x600", "2 Player Wind"){}
	  
	void on_accept() {
		Players = 2;
		difficulty = 6;
		screen_x_c = 512+300;
		Game_Model::get().score_needed = 20000;
		get_Game().push_state(new Play_State);
	}

} p2;
*//*
class Level_1 : public Text_Button
{
public:
    Level_1()
      : Text_Button(Point2f(300.0f, 50.0f)
		  , Point2f(500.0f, 100.0f)
		  , "system_36_800x600", "Level 1")
	{this->color = Color(1,0,0,1);}
	  
	void on_accept() {
		Players = 1;
		difficulty = 1;
		get_Game().push_state(new Play_State);
    }
} l1;

class Level_2 : public Text_Button
{
public:
    Level_2()
      : Text_Button(Point2f(300.0f, 125.0f)
		  , Point2f(500.0f, 175.0f)
		  , "system_36_800x600", "Level 2")
	{this->color = Color(1,0,1,1);}
	  
	void on_accept() {
		Players = 1;
		difficulty = 2;
		get_Game().push_state(new Play_State);
    }
} l2;

class Level_3 : public Text_Button
{
public:
    Level_3()
      : Text_Button(Point2f(300.0f, 200.0f)
		  , Point2f(500.0f, 250.0f)
		  , "system_36_800x600", "Level 3")
	{this->color = Color(1,0,1,0);}
	  
	void on_accept() {
		Players = 1;
		difficulty = 3;
		get_Game().push_state(new Play_State);
    }
} l3;
/*
class Level_4 : public Text_Button
{
public:
    Level_4()
      : Text_Button(Point2f(300.0f, 275.0f)
		  , Point2f(500.0f, 325.0f)
		  , "system_36_800x600", "Level 4")
	{this->color = Color(1,0,1,1);}
	  
	void on_accept() {
		difficulty = 4;
		Players = 1;
		screen_x_c = 512+50;
		Game_Model::get().score_needed = 10000;
		get_Game().push_state(new Play_State);
    }
} l4;

class Level_5 : public Text_Button
{
public:
    Level_5()
      : Text_Button(Point2f(300.0f, 350.0f)
		  , Point2f(500.0f, 400.0f)
		  , "system_36_800x600", "Level 5")
	{this->color = Color(1,0,1,1);}
	  
	void on_accept() {
		difficulty = 5;
		Players = 1;
		screen_x_c = 512+50;
		Game_Model::get().score_needed = 15000;
		get_Game().push_state(new Play_State);
    }
} l5;

class Level_6 : public Text_Button
{
public:
    Level_6()
      : Text_Button(Point2f(300.0f, 425.0f)
		  , Point2f(500.0f, 475.0f)
		  , "system_36_800x600", "Level 6 - Wind")
	{this->color = Color(1,0,1,1);}
	  
	void on_accept() {
		Players = 1;
		difficulty = 6;
		screen_x_c = 512+100;
		Game_Model::get().score_needed = 20000;
		get_Game().push_state(new Play_State);
    }
} l6;

*//*
 class Pop_Button : public Text_Button {
	  public:
    Pop_Button()
      : Text_Button(Point2f(600, 550.0f), Point2f(800, 600.0f), "system_36_800x600", "Main Menu")
    {
    }
	 void on_accept() {
      get_Game().pop_state();
    }

  } pop_button;

  
  */
  };





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
	int y_incr = 45;

	int screen_x_c = 300;

	Color col = Color(1.0,1.0,1,1);

	get_Fonts()["medium"].render_text(
		""
			, Point2f(screen_x_c + 10, y), col);

	get_Fonts()["small"].render_text(
		"Move: W A S D"
			, Point2f(screen_x_c + 20, y_incr + y), col);

	get_Fonts()["small"].render_text(
		"Shoot Soap: Left Mouse Button"
			, Point2f(screen_x_c + 10, y_incr*2 + y), col);
			
	get_Fonts()["small"].render_text(
		"Camera: Mouse"
			, Point2f(screen_x_c + 10, y_incr*3 + y), col);

	col = Color();

	get_Fonts()["small"].render_text(
		"Clean the water to get Points!\nGet as many points as possible before time runs out.\nThe longer you hold down soap, the larger the bubbles get.\nWhen your bubbles touches toxins, you will get points and the soap will decrease in size.\nTry hitting more than one toxin with the same soap for more points!\n"
			, Point2f(0 + 10, y_incr*8 + y), col);

	
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

      return new Title_State<Play_State, Instructions_State>("Winter Wars\n");
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
