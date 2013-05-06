#include "Team_Select_State.h"
#include "Utility.h"

void Team_Select_State::on_key(const SDL_KeyboardEvent &event) {
        if(event.keysym.sym == SDLK_ESCAPE && event.state == SDL_PRESSED){
            get_Game().pop_state();
        }
		else if(event.keysym.sym == SDLK_w && event.state == SDL_PRESSED){
			if(player_cursor[0] != 0)
				player_cursor[0] --;
		}
		else if(event.keysym.sym == SDLK_s && event.state == SDL_PRESSED){
			if(player_cursor[0] != 3)
				player_cursor[0] ++;
		}
		else if(event.keysym.sym == SDLK_a && event.state == SDL_PRESSED){
			if(player_cursor[0] == 0){
				player_gender_state[0] = (player_gender_state[0] + 1) % 2;
			}
			else if(player_cursor[event.which] == 2){
				player_control_state[event.which] = (player_control_state[event.which] + 1) % 2;
			}
			else if(player_cursor[event.which] == 3){
				player_sensitivity_state[event.which] = (player_sensitivity_state[event.which] + 9) % 10 + 1;
			}
			else{
				player_team_state[0] = (player_team_state[0] + 3) % 4;
			}
		}
		else if(event.keysym.sym == SDLK_d && event.state == SDL_PRESSED){
			if(player_cursor[0] == 0){
				player_gender_state[0] = (player_gender_state[0] + 1) % 2;
			}
			else if(player_cursor[event.which] == 2){
				player_control_state[event.which] = (player_control_state[event.which] + 1) % 2;
			}
			else if(player_cursor[event.which] == 3){
				player_sensitivity_state[event.which] = (player_sensitivity_state[event.which]) % 10 + 1;
			}
			else{
				player_team_state[0] = (player_team_state[0] + 1) % 4;
			}
		}
        else if(event.keysym.sym == SDLK_RETURN && event.state == SDL_PRESSED){
			if(player_state[0] != 2)
				player_state[0] ++;
			else{
				loading = true;
			}
		}
    }

void Team_Select_State::on_joy_hat(const SDL_JoyHatEvent &event) {

		if(player_state[event.which] == 1) {
			switch(event.value){
				case SDL_HAT_UP:    
					if(player_cursor[event.which] != 0)
						player_cursor[event.which] --;
					break;

				case SDL_HAT_LEFT:
					if(player_cursor[event.which] == 0){
						player_gender_state[event.which] = (player_gender_state[event.which] + 1) % 2;
					}
					else if(player_cursor[event.which] == 2){
						player_control_state[event.which] = (player_control_state[event.which] + 1) % 2;
					}
					else if(player_cursor[event.which] == 3){
						player_sensitivity_state[event.which] = (player_sensitivity_state[event.which] + 9) % 10 + 1;
					}
					else{
						player_team_state[event.which] = (player_team_state[event.which] + 3) % 4;
					}
					break;

				case SDL_HAT_RIGHT:
					if(player_cursor[event.which] == 0){
						player_gender_state[event.which] = (player_gender_state[event.which] + 1) % 2;
					}
					else if(player_cursor[event.which] == 2){
						player_control_state[event.which] = (player_control_state[event.which] + 1) % 2;
					}
					else if(player_cursor[event.which] == 3){
						player_sensitivity_state[event.which] = (player_sensitivity_state[event.which]) % 10 + 1;
					}
					else{
						player_team_state[event.which] = (player_team_state[event.which] + 1) % 4;
					}
					break;
				case SDL_HAT_DOWN:
					if(player_cursor[event.which] != 3)
						player_cursor[event.which] ++ ;
					break;
				//case SDL_HAT_RIGHTDOWN:
				default:
					break;
			}
		}
	}

void Team_Select_State::on_joy_button(const SDL_JoyButtonEvent &event){
		if(event.which == 0){ // player_1
			switch(event.button){
				case 0: // A
					if(event.state == SDL_PRESSED)	{
						if(player_state[0] != 2)
							player_state[0] ++;
						else{
							if(player_state[1] != 1 && player_state[2] != 1 && player_state[3] != 1)
							loading = true;
						}
					}
					break;
				case 1: // B
					if(event.state == SDL_PRESSED)	{
						if(player_state[0] != 0)
						player_state[0] --;
					}
					break;
				default:
					break;
			}
		}
		else{ // player_2 - 4
			switch(event.button){
				case 0: // A
					if(event.state == SDL_PRESSED)	{
						if(player_state[event.which] != 2)
							player_state[event.which] ++;
					}
					break;
				case 1: // B
					if(event.state == SDL_PRESSED)	{
						if(player_state[event.which] != 0)
							player_state[event.which] --;
					}
					break;
				default:
					break;
			}
		}
	}

void Team_Select_State::perform_logic(){

		if(start_game > 5.0f){

			vector<Player_info *> *player_list = new vector<Player_info*>;

			for(int player_idx = 0; player_idx < 4; player_idx ++){

				if(player_state[player_idx] != 2) continue;

				Player_info * newPlayer = new Player_info();

				newPlayer->genders_ = player_gender[player_idx];
				newPlayer->controls_ = player_control_state[player_idx];
				newPlayer->sensitivities_ = player_sensitivity_state[player_idx];


				if(player_team[player_idx] == "Green"){
					newPlayer->colors_ = 0;
				}
				else if(player_team[player_idx] == "Red"){
					newPlayer->colors_ = 1;
				}
				else if(player_team[player_idx] == "Blue"){
					newPlayer->colors_ = 2;
				}
				else if(player_team[player_idx] == "Orange"){
					newPlayer->colors_ = 3;
				}

				newPlayer->self_addr = RakNet::UNASSIGNED_SYSTEM_ADDRESS;

				player_list->push_back(newPlayer);
			}

			get_Sound().stop_BGM();
			get_Game().pop_state();
			get_Game().push_state(new Play_State_Base(player_list, "Claim Tree"));
		}


		for(int player_idx = 0; player_idx < 4; player_idx ++){
			if(player_gender_state[player_idx] == 0)
				player_gender[player_idx] = "Boy";
			else
				player_gender[player_idx] = "Girl";

			if(player_control_state[player_idx] == 0)
				player_control[player_idx] = "Normal";
			else
				player_control[player_idx] = "Invert";

			if(player_team_state[player_idx] == 0)
				player_team[player_idx] = "Green";
			else if(player_team_state[player_idx] == 1)
				player_team[player_idx] = "Red";
			else if(player_team_state[player_idx] == 2)
				player_team[player_idx] = "Blue";
			else
				player_team[player_idx] = "Orange";

		}
	}

void Team_Select_State::render() {
        Widget_Gamestate::render();

		render_image("Teamselect", Point2f(0.0f,0.0f), Point2f(1024.0f,1024.0f));
		get_Fonts()["system_36_800x600"].render_text("Player 1" ,Point2f(270, 30), Color(0x99FF1111));
		get_Fonts()["system_36_800x600"].render_text("Player 2" ,Point2f(750, 30), Color(0x99FF1111));
		get_Fonts()["system_36_800x600"].render_text("Player 3" ,Point2f(270, 330), Color(0x99FF1111));
		get_Fonts()["system_36_800x600"].render_text("Player 4" ,Point2f(750, 330), Color(0x99FF1111));

		for(int player_idx = 0; player_idx < 4; player_idx ++){

			render_image("Wanted",Point2f(-40.0f + player_render_offset[player_idx].x, 0.0f + player_render_offset[player_idx].y), Point2f(290.0f + player_render_offset[player_idx].x, 330.0f + player_render_offset[player_idx].y));

			if(player_state[player_idx] != 0){
				render_image("Snowball",Point2f(233.0f + player_render_offset[player_idx].x, 67.0f + 42.0f * player_cursor[player_idx] + player_render_offset[player_idx].y), Point2f(265.0f + player_render_offset[player_idx].x, 97.0f + 42.0f * player_cursor[player_idx] + player_render_offset[player_idx].y));
				get_Fonts()["cat"].render_text("Gender      > " + player_gender[player_idx] ,Point3f(265 + player_render_offset[player_idx].x, 72 + player_render_offset[player_idx].y, 0), Vector3f(0.28 ,0,0), Vector3f(0,0.28,0), Color(0x99FF1111));
				get_Fonts()["cat"].render_text("Team        > " + player_team[player_idx] ,Point3f(265 + player_render_offset[player_idx].x, 114 + player_render_offset[player_idx].y, 0), Vector3f(0.28 ,0,0), Vector3f(0,0.28,0), Color(0x99FF1111));
				get_Fonts()["cat"].render_text("Control     > " + player_control[player_idx] ,Point3f(265 + player_render_offset[player_idx].x, 156 + player_render_offset[player_idx].y, 0), Vector3f(0.28 ,0,0), Vector3f(0,0.28,0), Color(0x99FF1111));
				get_Fonts()["cat"].render_text("Sensitivity > " + itoa(player_sensitivity_state[player_idx]) ,Point3f(265 + player_render_offset[player_idx].x, 198 + player_render_offset[player_idx].y, 0), Vector3f(0.28 ,0,0), Vector3f(0,0.28,0), Color(0x99FF1111));
				render_image(player_gender[player_idx] + player_team[player_idx] + "Regular", Point2f(55 + player_render_offset[player_idx].x,125 + player_render_offset[player_idx].y),Point2f(188 + player_render_offset[player_idx].x,258 + player_render_offset[player_idx].y));
			}
			else
				render_image("Join",Point2f(250.0f + player_render_offset[player_idx].x, 100.0f + player_render_offset[player_idx].y), Point2f(400.0f + player_render_offset[player_idx].x, 250.0f + player_render_offset[player_idx].y));

			if(player_state[player_idx] >= 2){
				render_image("Ready",Point2f(100.0f + player_render_offset[player_idx].x, 70.0f + player_render_offset[player_idx].y), Point2f(430.0f + player_render_offset[player_idx].x, 400.0f + player_render_offset[player_idx].y));
			}
		}

		if(player_state[0] == 2)
			get_Fonts()["system_36_800x600"].render_text("P1 Press A to continue" ,Point2f(510, 568), Color(0xFF000000));

		if(loading){
			render_image("Loading", Point2f(0.0f,0.0f), Point2f(1024.0f,1024.0f));
			start_game += 1.0f;
		}


    }
