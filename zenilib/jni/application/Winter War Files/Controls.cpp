#include "Controls.h"

using namespace std;
using namespace Zeni;

Controls::Controls(bool inverted_)
{
}


Controls::~Controls(void)
{
}

bool Controls::take_input(const SDL_Event &event)	{
	//Yes I realize this does nothing right now, but it is where
		//we can incorporate the keyboard (for hacks)
		bool Handled_Input = true;

		switch(event.key.keysym.sym)	{
		case SDLK_UP:
			input.left_x = 1.0 * (event.type == SDL_KEYDOWN);
			break;
		case SDLK_DOWN:
			input.left_x = -1 * (event.type == SDL_KEYDOWN);
			break;
		case SDLK_LEFT:
			input.left_y = 1 * (event.type == SDL_KEYDOWN);
			break;
		case SDLK_RIGHT:
			input.left_y = -1 * (event.type == SDL_KEYDOWN);
			break;


		case SDLK_w:
			input.left_x = 1 * (event.type == SDL_KEYDOWN);
			break;
		case SDLK_s:
			input.left_x = -1 * (event.type == SDL_KEYDOWN);
			break;
		case SDLK_d:
			input.left_y = -1 * (event.type == SDL_KEYDOWN);
			break;
		case SDLK_a:
			input.left_y = 1 * (event.type == SDL_KEYDOWN);
			break;

		case SDLK_SPACE:
			input.jump = event.type == SDL_KEYDOWN;

		default:
			Handled_Input = false;
			break;
		}
		return Handled_Input;
}

bool Controls::take_input(const Zeni::Zeni_Input_ID &Zid, const float &confidence, const int &action)	{
	bool Handled_Input = true;

	switch(action)	{

		case L_TRIG:
			//currently left trigger pressed so do something
			/*test.input.build_view = true;
			test.input.jump = true;*/
			break;
		/*case R_TRIG:
			
			break;
*/
		
		case RSTICK_X:
			input.right_x = confidence;
			break;
		case RSTICK_Y:
			input.right_y = confidence;
			break;
		case LSTICK_X:
			input.left_x = confidence;
			break;
		case LSTICK_Y:
			input.left_y = confidence;
			break;

		default:
			Handled_Input = false;
			break;
	}

	return Handled_Input;
}
