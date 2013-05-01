#include "Tutorial_Level.h"
#include "Objective.h"
#include "Player.h"


using namespace std;

Tutorial_Level::Tutorial_Level()
{
	current_objective = new Build_a_Healing_Pool();
	get_player(0)->add_message(current_objective->get_message_to_display());
	
}

Tutorial_Level::~Tutorial_Level()
{
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
		//Make success doobers happen hear
		current_objective = current_objective->get_next_Objective();
		get_player(0)->add_message(current_objective->get_message_to_display());
	}

	//Not sure how to tell the view to display hints, but this is where to get it
	//current_objective->get_message_to_display();
}

