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
	const Color bgc = cr["lightblueop"];
	const Color box = cr["console_border"];
	const Color blk = cr["black"];

	get_Fonts()["cat_110"].render_text("Team " + winning_team + " Win!" ,Point2f(690, 110), winning_color);
	Font &font_36 = get_Fonts()["cat_36"];
	Font &font_64 = get_Fonts()["cat_64"];

	const Quadrilateral<Vertex2f_Color> boxx(   Vertex2f_Color(Point2f(50, 300), box),
												Vertex2f_Color(Point2f(50, 625), box),
												Vertex2f_Color(Point2f(1850, 625), box),
												Vertex2f_Color(Point2f(1850, 300), box));
    vr.render(boxx);

	get_Fonts()["cat_64"].render_text("PLAYER STATS | " ,Point2f(50, 300), blk);
	get_Fonts()["cat_64"].render_text("TEAM STATS" ,Point2f(50, 650), blk);

	get_Fonts()["cat_36"].render_text("PLAYER 1" ,Point2f(75, 400), blk);
	get_Fonts()["cat_36"].render_text("PLAYER 2" ,Point2f(75, 450), blk);
	get_Fonts()["cat_36"].render_text("PLAYER 3" ,Point2f(75, 500), blk);
	get_Fonts()["cat_36"].render_text("PLAYER 4" ,Point2f(75, 550), blk);

	float cur_width = font_64.get_text_width("PLAYER STATS | ") + 50.0f + 30.0f;

	get_Fonts()["cat_36"].render_text("Kills | " ,Point2f(cur_width, 320), blk);
	cur_width+=(font_36.get_text_width("Kills | "));
	get_Fonts()["cat_36"].render_text("Deaths | " ,Point2f(cur_width, 320), blk);
	cur_width+=(font_36.get_text_width("Deaths | "));
	get_Fonts()["cat_36"].render_text("Accuracy | " ,Point2f(cur_width, 320), blk);
	cur_width+=(font_36.get_text_width("Accuracy | "));
	get_Fonts()["cat_36"].render_text("Damage Dealt | " ,Point2f(cur_width, 320), blk);
	cur_width+=(font_36.get_text_width("Damage Dealt | "));
	get_Fonts()["cat_36"].render_text("Damage Taken | " ,Point2f(cur_width, 320), blk);
	cur_width+=(font_36.get_text_width("Damage Taken | "));
	get_Fonts()["cat_36"].render_text("Structure Destroyed | " ,Point2f(cur_width, 320), blk);
	cur_width+=(font_36.get_text_width("Structure Destroyed | "));
	get_Fonts()["cat_36"].render_text("Structure Built | " ,Point2f(cur_width, 320), blk);

	for (int i = 0 ; i < 4; i++){
		Player * player = Game_Model::get().get_player(i);
		Player::Stats stat = player->stats;  

		get_Fonts()["cat_36"].render_text(itoa(stat.kills) ,Point2f(525, 400 + 50 * i), blk);
		get_Fonts()["cat_36"].render_text(itoa(stat.deaths) ,Point2f(660, 400 + 50 * i), blk);

		if(stat.thrown != 0)
			get_Fonts()["cat_36"].render_text(itoa((stat.hit * 100/stat.thrown)) + " %" ,Point2f(750, 400 + 50 * i), blk);
		else
			get_Fonts()["cat_36"].render_text("0 %" ,Point2f(750, 400 + 50 * i), blk);

		get_Fonts()["cat_36"].render_text(itoa(stat.damage_dealt) ,Point2f(900, 400 + 50 * i), blk);
		get_Fonts()["cat_36"].render_text(itoa(stat.damage_taken) ,Point2f(1100, 400 + 50 * i), blk);
		get_Fonts()["cat_36"].render_text(itoa(stat.destroyed) ,Point2f(1425, 400 + 50 * i), blk);
		get_Fonts()["cat_36"].render_text(itoa(stat.built) ,Point2f(1650, 400 + 50 * i), blk);

	}

	if(cursor == 0){
		get_Fonts()["cat_100"].render_text("MANU" ,Point2f(500, 930), Color(0x9911FF11));
		get_Fonts()["cat_100"].render_text("RESTART" ,Point2f(1200, 930), blk);

		const Quadrilateral<Vertex2f_Color> bg( Vertex2f_Color(Point2f(480, 910), bgc),
												Vertex2f_Color(Point2f(480, 1050), bgc),
												Vertex2f_Color(Point2f(750, 1050), bgc),
												Vertex2f_Color(Point2f(750, 910), bgc));
        vr.render(bg);
	}
	else if(cursor == 1){
		get_Fonts()["cat_100"].render_text("MENU" ,Point2f(500, 930), blk);
		get_Fonts()["cat_100"].render_text("RESTART" ,Point2f(1200, 930), Color(0x9911FF11));

		const Quadrilateral<Vertex2f_Color> bg( Vertex2f_Color(Point2f(1180, 910), bgc),
												Vertex2f_Color(Point2f(1180, 1050), bgc),
												Vertex2f_Color(Point2f(1570, 1050), bgc),
												Vertex2f_Color(Point2f(1570, 910), bgc));
        vr.render(bg);
	}
	
}