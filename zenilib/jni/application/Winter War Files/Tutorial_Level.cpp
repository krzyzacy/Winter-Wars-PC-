#include "Tutorial_Level.h"
#include "Objective.h"

using namespace std;

Tutorial_Level::Tutorial_Level()
{
	current_objective = new 

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

	}

	//Not sure how to tell the view to display hints, but this is where to get it
	current_objective->get_message_to_display();
}

