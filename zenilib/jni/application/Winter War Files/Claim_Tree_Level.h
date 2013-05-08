
#ifndef CLAIM_TREE_LEVEL_H
#define CLAIM_TREE_LEVEL_H

#include "Level.h"

class Claim_Tree_Level : public Level
{	
protected:
	void update();
	void start_up(const std::vector<Player_info*> &player_info);

	//// returns true if some team has won
	//// stops the clock if yes
	bool win() override;

	///*set the time to win and the team to win*/
	//void tree_claimed(const Team *);

	///* return time until someone wins */
	//float time_till_win() const;

	///* return time game has been played*/
	//float get_time() const;
	
		
};

#endif