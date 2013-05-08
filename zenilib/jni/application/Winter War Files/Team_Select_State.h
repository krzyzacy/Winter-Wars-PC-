#include <zenilib.h>

#include "Play_State_Base.h"

#include "String.h"
#include <vector>


using namespace std;
using namespace Zeni;



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
			player_sensitivity_state[player_idx]  = 5;
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
		keyboard_index = 0;

		get_Sound().set_BGM("sfx/drum");
		get_Sound().set_BGM_looping(1);
		get_Sound().play_BGM();
    }
    
private:
    void on_key(const SDL_KeyboardEvent &event);

	void on_joy_hat(const SDL_JoyHatEvent &event);

	void on_joy_button(const SDL_JoyButtonEvent &event);
    
	void perform_logic();

    void render();
    
	int player_state[4];
    int player_team_state[4];
	int player_gender_state[4];
	int player_control_state[4];
	int player_sensitivity_state[4];
	int player_cursor[4];
	String player_gender[4];
	String player_team[4];
	String player_control[4];

	Point2f player_render_offset[4];
	bool loading;
	float start_game;
	int keyboard_index;

	vector<int> colors_;
	vector<Zeni::String> genders_;
	vector<int> controls_;
	vector<int> sensitivities_;
	//Point2f player_render_base;
};