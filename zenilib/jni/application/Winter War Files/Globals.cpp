
#include "Globals.h"

#include "Structure.h"

void Game_Parameter::increment()
{
	current_value += unit_increment;

	if (current_value > max)
		current_value = max;
}

void Game_Parameter::decrement()
{
	current_value -= unit_increment;

	if (current_value < min)
		current_value = min;
}

void Game_Parameter::reset()
{
	current_value = default_value;
}

Parameter_List parameters;

Parameter_List::Parameter_List()
{
	list.push_back(Game_Parameter("Snowman Health", Build_Cost[SNOWMAN], 1000, 10, 10));
	list.push_back(Game_Parameter("Fort Health", Build_Cost[FORT], 1000, 10, 10));
	list.push_back(Game_Parameter("Snow_Factory Health", Build_Cost[SNOW_FACTORY], 1000, 10, 10));
	list.push_back(Game_Parameter("Healing_Pool Health", Build_Cost[HEALING_POOL], 1000, 10, 10));

	list.push_back(Game_Parameter("Snowman Cost", Struct_Integrity[SNOWMAN], 10000, 100, 10));
	list.push_back(Game_Parameter("Fort Cost", Struct_Integrity[FORT], 10000, 100, 10));
	list.push_back(Game_Parameter("Snow_Factory Cost", Struct_Integrity[SNOW_FACTORY], 10000, 100, 10));
	list.push_back(Game_Parameter("Healing_Pool Cost", Struct_Integrity[HEALING_POOL], 10000, 100, 10));
}


void Parameter_List::reset_all()
{
	for (int i = 0 ; i < size() ; i++)
		at(i).reset();
}