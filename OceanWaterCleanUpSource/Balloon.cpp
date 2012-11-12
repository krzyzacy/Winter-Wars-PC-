#include "Balloon.h"

#include "Multiplier.h"
#include "Utility.h"

#include "Game_Model.h"


#include <zenilib.h>
#include <vector>

using namespace Zeni;
using namespace std;

const int Balloon::balloon_ID_c = 1;

Balloon::~Balloon(void)
{	 
	remove_multipliers();
}

void Balloon::render() const
{
	Game_Object::render(image);
}

void Balloon::update()
{
	if (Game_Model::get().helium)
		accelerate(5.0f, up_c);



	float air_factor = 1;

	if (get_velo().y >= 0)
		remove_multipliers();
	else
		air_factor = 1;


	// add air resistance
	accelerate(air_factor * air_res_c * area * get_speed()
		, get_dir() - Global::pi);
	
	Game_Object::update();

	if (Game_Model::get().get_time_left() < 0 && !Game_Model::get().helium)
		Game_Model::get().pop_balloon(this);
}

void Balloon::pass(Balloon &B, const Point2f &pos)
{
	int B_size = B.multipliers.size();
	for (int i = 0 ; i < multipliers.size() ; i++)
	{
		B.multipliers.push_back(new Multiplier(*multipliers.at(i), pos));
	}
	for (int i = 0 ; i < B_size ; i++)
	{
		multipliers.push_back(new Multiplier(*B.multipliers.at(i), pos));
	}
	play_sound("bounce");

}

void Balloon::remove_multipliers()
{
	for (int i = 0 ; i < multipliers.size() ; i++)
	{
		delete multipliers[i];
	}
	multipliers.clear();
}