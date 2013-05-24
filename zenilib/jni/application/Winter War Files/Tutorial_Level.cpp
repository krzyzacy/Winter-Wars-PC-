#include "Tutorial_Level.h"
#include "Objective.h"
#include "Player.h"
#include "Structure.h"

using namespace std;

#include "Globals.h"

Tutorial_Level::Tutorial_Level()
{	
	parameters.find("Starting Resources").set_value(7000);
}

Tutorial_Level::~Tutorial_Level() 
{
	parameters.find("Starting Resources").reset();
}

string Tutorial_Level::get_level_name()
{
	return "Tutorial_Level";
}

void Tutorial_Level::start_up(const std::vector<Player_info*> &player_info)
{
	Claim_Tree_Level::start_up(player_info);

	current_objective = new Use_Tips();
	
	get_player(0)->add_message(current_objective->get_message_to_display(), 10000, 100);


}

void Tutorial_Level::clean()
{	
	Claim_Tree_Level::clean();

	delete current_objective;
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
		Objective *old_ob = current_objective;

		//Make success doobers happen here
		current_objective = current_objective->get_next_Objective();
		
		delete old_ob;
		
		get_player(0)->add_message(current_objective->get_message_to_display(), 10000, 100);
	}

	//Not sure how to tell the view to display hints, but this is where to get it
	//current_objective->get_message_to_display();
}

