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
	if(event.which == 0){ // player 1 control the end game screen
	
		switch(event.value){
		
			case SDL_HAT_LEFT:
				cursor = 0;
				break;

			case SDL_HAT_RIGHT:
				cursor = 1;
				break;

			default:
				break;
		}
	}
}

void End_Game_State::on_joy_button(const SDL_JoyButtonEvent &event) {
	if(event.which == 0){
		switch(event.button){
			case 0: // A
				if(event.state == SDL_PRESSED)
					confirm = true;
				break;
				
			default:
				break;
		}
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
	if(confirm && cursor == 0){ // back to main menu
		get_Game().pop_state();
		get_Game().pop_state();
		get_Game().pop_state();
	}
	if(confirm && cursor == 1){ // restart game
		get_Game().pop_state();
	}
}

void End_Game_State::render() {
	get_Video().set_2d(make_pair(Point2f(0.0f, 0.0f), Point2f(1920.0f, 1200.0f)), true);
	render_image("Endscreen", Point2f(0.0f,0.0f), Point2f(2048.0f,2048.0f));

	Team *winning_team = Game_Model::get().get_team(Game_Model::get().get_World()->get_center_Tile()->get_team() - 1);
	

	Colors &cr = get_Colors();
	Video &vr = get_Video();
	const Color winning_color = cr[winning_team->get_name()];
	const Color bgc = cr["lightblueop"];
	const Color box = cr["console_border"];
	const Color blk = cr["black"];

	get_Fonts()["cat_110"].render_text( winning_team->get_name_Upper_Case() + " Team" + " Wins!" ,Point2f(670, 110), winning_color);
	Font &font_36 = get_Fonts()["cat_36"];
	Font &font_64 = get_Fonts()["cat_64"];

	const Quadrilateral<Vertex2f_Color> boxx(   Vertex2f_Color(Point2f(50, 300), box),
												Vertex2f_Color(Point2f(50, 625), box),
												Vertex2f_Color(Point2f(1850, 625), box),
												Vertex2f_Color(Point2f(1850, 300), box));
    vr.render(boxx);

	get_Fonts()["cat_64"].render_text("PLAYER STATS | " ,Point2f(50, 300), blk);

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
		const Color player_color = cr[player->get_team()->get_name()];
		
		get_Fonts()["cat_36"].render_text("PLAYER " + itoa(i) ,Point2f(75, 400 + 50 * i), player_color);

		get_Fonts()["cat_36"].render_text(itoa(stat.kills) ,Point2f(525, 400 + 50 * i), player_color);
		get_Fonts()["cat_36"].render_text(itoa(stat.deaths) ,Point2f(660, 400 + 50 * i), player_color);

		if(stat.thrown != 0)
			get_Fonts()["cat_36"].render_text(itoa((stat.hit * 100/stat.thrown)) + " %" ,Point2f(750, 400 + 50 * i), player_color);
		else
			get_Fonts()["cat_36"].render_text("0 %" ,Point2f(750, 400 + 50 * i), player_color);

		get_Fonts()["cat_36"].render_text(itoa(stat.damage_dealt) ,Point2f(900, 400 + 50 * i), player_color);
		get_Fonts()["cat_36"].render_text(itoa(stat.damage_taken) ,Point2f(1100, 400 + 50 * i), player_color);
		get_Fonts()["cat_36"].render_text(itoa(stat.destroyed) ,Point2f(1425, 400 + 50 * i), player_color);
		get_Fonts()["cat_36"].render_text(itoa(stat.built) ,Point2f(1650, 400 + 50 * i), player_color);

	}

	
	
	/*RENDER TEAM STATS*/
	get_Fonts()["cat_64"].render_text("TEAM STATS" ,Point2f(50, 650), blk);


	cur_width = font_64.get_text_width("TEAM STATS | ") + 50.0f + 30.0f;
	int width_array[10];

	width_array[0] = cur_width;
	get_Fonts()["cat_36"].render_text("Final Network | " ,Point2f(cur_width, 670), blk);
	cur_width+=(font_36.get_text_width("Final Network | "));
	width_array[0] += (cur_width - width_array[0])/2;

	width_array[1] = cur_width;
	get_Fonts()["cat_36"].render_text("Largest Network | " ,Point2f(cur_width, 670), blk);
	cur_width+=(font_36.get_text_width("Largest Network | "));
	width_array[0] += (cur_width - width_array[1])/2;

	width_array[2] = cur_width;
	get_Fonts()["cat_36"].render_text("Tiles Lost | " ,Point2f(cur_width, 670), blk);
	cur_width+=(font_36.get_text_width("Tiles Lost | "));
	width_array[0] += (cur_width - width_array[2])/2;

	width_array[3] = cur_width;
	get_Fonts()["cat_36"].render_text("Gold Spent | " ,Point2f(cur_width, 670), blk);
	cur_width+=(font_36.get_text_width("Gold Spent | "));
	width_array[0] += (cur_width - width_array[3])/2;

	width_array[4] = cur_width;
	get_Fonts()["cat_36"].render_text("Snowmen | " ,Point2f(cur_width, 670), blk);
	cur_width+=(font_36.get_text_width("Snowmen | "));
	width_array[0] += (cur_width - width_array[4])/2;

	width_array[5] = cur_width;
	get_Fonts()["cat_36"].render_text("Forts | " ,Point2f(cur_width, 670), blk);
	cur_width+=(font_36.get_text_width("Forts | "));
	width_array[0] += (cur_width - width_array[5])/2;

	width_array[6] = cur_width;
	get_Fonts()["cat_36"].render_text("Factory | " ,Point2f(cur_width, 670), blk);
	cur_width+=(font_36.get_text_width("Factory | "));
	width_array[0] += (cur_width - width_array[6])/2;

	width_array[7] = cur_width;
	get_Fonts()["cat_36"].render_text("Healing Pools | " ,Point2f(cur_width, 670), blk);
	cur_width+=(font_36.get_text_width("Healing Pools | "));
	width_array[0] += (cur_width - width_array[7])/2;

	int valid = -1;
	for (int i = 0 ; i < 4; i++){
		Team *team = Game_Model::get().get_team(i);
		if(team->is_empty())
			continue;
		else
			valid++;
		Team::Stats stat = team->stats;
		cur_width = font_64.get_text_width("TEAM STATS | ") + 50.0f + 30.0f;
		const Color team_color = cr[team->get_name()];
		
	
		get_Fonts()["cat_36"].render_text(team->get_name_Upper_Case() + " Team" ,Point2f(75, 700 + 50 * valid), team_color);

		get_Fonts()["cat_36"].render_text(itoa(stat.final_network) ,Point2f(width_array[0], 700 + 50 * valid), team_color);
		get_Fonts()["cat_36"].render_text(itoa(stat.largest_network) ,Point2f(width_array[1], 700 + 50 * valid), team_color);
		get_Fonts()["cat_36"].render_text(itoa(stat.tiles_lost) ,Point2f(width_array[2], 700 + 50 * valid), team_color);
		get_Fonts()["cat_36"].render_text(itoa(stat.resources_spent) ,Point2f(width_array[3], 700 + 50 * valid), team_color);


		get_Fonts()["cat_36"].render_text(itoa(stat.structures[1]) ,Point2f(width_array[4], 700 + 50 * valid), team_color);
		get_Fonts()["cat_36"].render_text(itoa(stat.structures[2]) ,Point2f(width_array[5], 700 + 50 * valid), team_color);
		get_Fonts()["cat_36"].render_text(itoa(stat.structures[3]) ,Point2f(width_array[6], 700 + 50 * valid), team_color);
		get_Fonts()["cat_36"].render_text(itoa(stat.structures[4]) ,Point2f(width_array[7], 700 + 50 * valid), team_color);

	}



	if(cursor == 0){
		get_Fonts()["cat_100"].render_text("MENU" ,Point2f(500, 930), Color(0x9911FF11));
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
	else if(cursor == 2){
		get_Fonts()["cat_100"].render_text("MENU" ,Point2f(500, 930), blk);
		get_Fonts()["cat_100"].render_text("RESTART" ,Point2f(1200, 930), blk);
	}
	
}