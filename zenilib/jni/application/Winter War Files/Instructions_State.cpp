#include "Instructions_State.h"

void Instructions_State::on_key(const SDL_KeyboardEvent &event) {
	if(event.keysym.sym == SDLK_ESCAPE && event.state == SDL_PRESSED)
		get_Game().pop_state();
		if(event.keysym.sym == SDLK_RETURN && event.state == SDL_PRESSED){
			state ++;
			if(state == 7)
				get_Game().pop_state();
	}
}

void Instructions_State::on_joy_button(const SDL_JoyButtonEvent &event) {
	switch(event.button){
		case 0: // A
			if(event.state == SDL_PRESSED)	{
				state ++;
				if(state == 7)
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

void Instructions_State::render(){
	Widget_Gamestate::render();

	get_Video().set_2d(make_pair(Point2f(0.0f, 0.0f), Point2f(1920.0f, 1200.0f)), true);
	if(state == 0){
		render_image("Control_1", Point2f(0.0f,0.0f), Point2f(2048.0f,2048.0f));
	}
	if(state == 1){
		render_image("Control_2", Point2f(0.0f,0.0f), Point2f(2048.0f,2048.0f));
	}
	if(state == 2){
		render_image("Objective", Point2f(0.0f,0.0f), Point2f(2048.0f,2048.0f));
	}
	if(state == 3){
		render_image("World", Point2f(0.0f,0.0f), Point2f(2048.0f,2048.0f));
	}
	if(state == 4){
		render_image("HUD", Point2f(0.0f,0.0f), Point2f(2048.0f,2048.0f));
	}
	if(state == 5){
		render_image("Instructions", Point2f(0.0f,0.0f), Point2f(2048.0f,2048.0f));
	}
	if(state == 6){
		render_image("StillConfused", Point2f(0.0f,0.0f), Point2f(2048.0f,2048.0f));
	}
  
	render_controls(0);
}