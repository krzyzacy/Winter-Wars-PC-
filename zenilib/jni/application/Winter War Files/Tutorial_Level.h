#ifndef __TUTORIAL_LEVEL_H__
#define __TUTORIAL_LEVEL_H__


#include "Claim_Tree_Level.h"

class Objective;

class Tutorial_Level : public Claim_Tree_Level
{
public:
	Tutorial_Level();
	~Tutorial_Level();

	std::string get_level_name() override;
	
	void start_up(const std::vector<Player_info*> &player_info) override;
	void clean() override;

	void update() override;
	
private:
	Objective* current_objective;
	//The base funtions should work for everythign else. 
	

};

#endif