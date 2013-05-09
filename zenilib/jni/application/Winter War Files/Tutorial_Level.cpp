#include "Tutorial_Level.h"
#include "Objective.h"
#include "Player.h"
#include "Structure.h"

using namespace std;

#include "Globals.h"

Tutorial_Level::Tutorial_Level()
{
	current_objective = new Build_Structure(HEALING_POOL);
	
	parameters.find("Snow Factory Intake per Second").get_value();

}

Tutorial_Level::~Tutorial_Level() 
{}

string Tutorial_Level::get_level_name()
{
	return "Tutorial_Level";
}

void Tutorial_Level::start_up(const std::vector<Player_info*> &player_info)
{
	Claim_Tree_Level::start_up(player_info);
	
	get_player(0)->add_message(current_objective->get_message_to_display(),0, 10);
}

void Tutorial_Level::update()
{
	Claim_Tree_Level::update();

	if(current_objective == NULL)
	{
		//Do somethign for winning and end the tutorial
		//For Now just ignore it
		return;
	}

	if(current_objective->has_been_completed())
	{
		//Make success doobers happen here
		current_objective = current_objective->get_next_Objective();
		// You didn't delete the objective!!!!
		
		
		get_player(0)->add_message(current_objective->get_message_to_display(), 0, 10);
	}

	//Not sure how to tell the view to display hints, but this is where to get it
	//current_objective->get_message_to_display();
}

