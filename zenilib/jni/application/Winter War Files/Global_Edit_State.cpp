#include "Global_Edit_State.h"
#include "Globals.h"

Global_Edit_State::Global_Edit_State()
    : Widget_Gamestate(make_pair(Point2f(0.0f, 0.0f), Point2f(800.0f, 600.0f)))
{
	get_Game().joy_mouse.enabled = true;
	size = parameters.size();
	cursor = 0;
}

void Global_Edit_State::on_key(const SDL_KeyboardEvent &event) 
{
    if(event.keysym.sym == SDLK_ESCAPE && event.state == SDL_PRESSED)
      get_Game().pop_state();

	if(event.keysym.sym == SDLK_UP && event.state == SDL_PRESSED)
      cursor = (cursor + 1) % size;

	if(event.keysym.sym == SDLK_DOWN && event.state == SDL_PRESSED)
      cursor = (cursor + size - 1) % size;

	if(event.keysym.sym == SDLK_LEFT && event.state == SDL_PRESSED)
	  parameters.at(cursor).decrement();

	if(event.keysym.sym == SDLK_RIGHT && event.state == SDL_PRESSED)
      parameters.at(cursor).increment();

}


void Global_Edit_State::render()
{
    Widget_Gamestate::render();
	get_Fonts()["system_36_800x600"].render_text("GLOBAL CONSTANTS EDITOR" ,Point2f(155, 60), Color(0xFF33BBE8));

	//get_Fonts()["system_36_800x600"].render_text(parameters.at(cursor).name ,Point3f(20, 120 + 50, 0), Vector3f(0.8,0,0), Vector3f(0,0.8,0), Color(0xFF33BBE8));
	//get_Fonts()["system_36_800x600"].render_text(itoa(parameters.at(cursor).get_value()) ,Point3f(300, 120 + 50, 0), Vector3f(0.8,0,0), Vector3f(0,0.8,0), Color(0xFF33BBE8));

	for(int i = 0; i < 5; i++){
		if(i == 2){
			get_Fonts()["system_36_800x600"].render_text(">>" ,Point3f(0, 120 + 50 * i, 0),Vector3f(0.8,0,0), Vector3f(0,0.8,0), Color(0xFFFF0000));
			get_Fonts()["system_36_800x600"].render_text(parameters.at((cursor - 2 + i + size) % size).name ,Point3f(35, 120 + 50 * i, 0),Vector3f(0.8,0,0), Vector3f(0,0.8,0), Color(0xFFFF0000));
			get_Fonts()["system_36_800x600"].render_text(itoa(parameters.at((cursor - 2 + i + size) % size).get_value()) ,Point3f(300, 120 + 50 * i, 0), Vector3f(0.8,0,0), Vector3f(0,0.8,0), Color(0xFFFF0000));
			continue;
		}


		get_Fonts()["system_36_800x600"].render_text(parameters.at((cursor - 2 + i + size) % size).name ,Point3f(35, 120 + 50 * i, 0),Vector3f(0.8,0,0), Vector3f(0,0.8,0), Color(0xFF33BBE8));
		get_Fonts()["system_36_800x600"].render_text(itoa(parameters.at((cursor - 2 + i + size) % size).get_value()) ,Point3f(300, 120 + 50 * i, 0), Vector3f(0.8,0,0), Vector3f(0,0.8,0), Color(0xFF33BBE8));
	}

	//get_Video().set_2d(make_pair(Point2f(0.0f, 0.0f), Point2f(1920.0f, 1200.0f)), true);
	//render_image("ts800", Point2f(0.0f,0.0f), Point2f(1024.0f, 1024.0f));
	render_controls(0);
}