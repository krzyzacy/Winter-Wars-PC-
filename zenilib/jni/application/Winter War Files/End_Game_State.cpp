#include "End_Game_State.h"

#include "Game_Model.h"
#include "Controls.h"
#include "View.h"
#include "Player.h"
#include "Player_View.h"
#include "Permanent.h"
#include "World.h"
#include "Tile.h"
#include "Team.h"

void End_Game_State::on_pop()	{
	Game_Model::get().restart();
}

void End_Game_State::on_joy_hat(const SDL_JoyHatEvent &event)	{
			
		if(cursor == 0) {
			switch(event.value){
			
				case SDL_HAT_LEFT:
					cursor = 0;
					break;

				case SDL_HAT_RIGHT:
					cursor = 1;
					break;

				//case SDL_HAT_RIGHTDOWN:
				default:
					break;
			}
		}
}

void End_Game_State::on_joy_button(const SDL_JoyButtonEvent &event) {
	switch(event.button){
		case 0: // A
			if(event.state == SDL_PRESSED)	{
				confirm = true;
			}
			break;
		case 1: // B
			if(event.state == SDL_PRESSED)	{
				confirm = false;
			}
			break;
		default:
			break;
	}
}

void End_Game_State::on_key(const SDL_KeyboardEvent &event) {
	if(event.keysym.sym == SDLK_ESCAPE && event.state == SDL_PRESSED){
		get_Game().pop_state();
	}
	else if(event.keysym.sym == SDLK_a && event.state == SDL_PRESSED){
		cursor = 0;
	}
	else if(event.keysym.sym == SDLK_d && event.state == SDL_PRESSED){
		cursor = 1;
	}
	else if(event.keysym.sym == SDLK_RETURN && event.state == SDL_PRESSED){
		confirm = true;
	}
} 

void End_Game_State::perform_logic(){
	if(confirm && cursor == 0){
		get_Game().pop_state();
		get_Game().pop_state();
		get_Game().pop_state();
	}
	if(confirm && cursor == 1){
		get_Game().pop_state();
	}
}

void End_Game_State::render() {
	get_Video().set_2d(make_pair(Point2f(0.0f, 0.0f), Point2f(1920.0f, 1200.0f)), true);
	render_image("Endscreen", Point2f(0.0f,0.0f), Point2f(2048.0f,2048.0f));

	Zeni::String winning_team;
	switch(Game_Model::get().get_World()->get_center_Tile()->get_team()){
		case GREEN:
			winning_team = "green";
			break;

		case RED:
			winning_team = "red";
			break;

		case BLUE:
			winning_team = "blue";
			break;

		case ORANGE:
			winning_team = "orange";
			break;

		default:
			break;
	}

	Colors &cr = get_Colors();
	Video &vr = get_Video();
	const Color winning_color = cr[winning_team];
	const Color bgc = cr["default_button_bg_hovered_strayed"];

	get_Fonts()["cat_100"].render_text("Team " + winning_team + " Win!" ,Point2f(700, 75), winning_color);

	get_Fonts()["cat_100"].render_text("TEAM STATS" ,Point2f(150, 250), Color(0x99FF1111));
	get_Fonts()["cat_100"].render_text("PLAYER STATS" ,Point2f(150, 600), Color(0x99FF1111));

	if(cursor == 0){
		get_Fonts()["cat_100"].render_text("MANU" ,Point2f(500, 930), Color(0x9911FF11));
		get_Fonts()["cat_100"].render_text("RESTART" ,Point2f(1200, 930), Color(0x99FF1111));

		const Quadrilateral<Vertex2f_Color> bg( Vertex2f_Color(Point2f(480, 900), bgc),
												Vertex2f_Color(Point2f(480, 1060), bgc),
												Vertex2f_Color(Point2f(750, 1060), bgc),
												Vertex2f_Color(Point2f(750, 900), bgc));
        vr.render(bg);
	}
	else if(cursor == 1){
		get_Fonts()["cat_100"].render_text("MANU" ,Point2f(500, 930), Color(0x99FF1111));
		get_Fonts()["cat_100"].render_text("RESTART" ,Point2f(1200, 930), Color(0x9911FF11));

		const Quadrilateral<Vertex2f_Color> bg( Vertex2f_Color(Point2f(1180, 900), bgc),
												Vertex2f_Color(Point2f(1180, 1060), bgc),
												Vertex2f_Color(Point2f(1600, 1060), bgc),
												Vertex2f_Color(Point2f(1600, 900), bgc));
        vr.render(bg);
	}
	
}