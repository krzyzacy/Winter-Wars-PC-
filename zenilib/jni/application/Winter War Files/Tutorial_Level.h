#ifndef __TUTORIAL_LEVEL_H__
#define __TUTORIAL_LEVEL_H__


#include "Claim_Tree_Level.h"

class Objective;

class Tutorial_Level : public Claim_Tree_Level
{
public:
	Tutorial_Level();
	~Tutorial_Level();
	

	void update();
	
private:
	Objective* current_objective;
	//The base funtions should work for everythign else. 
	

};

#endif