#pragma once

#include "Player_View.h"

class Player;

class Player_Claim_Tree_View : public Player_View
{
public:
	Player_Claim_Tree_View(Player* p);
	virtual ~Player_Claim_Tree_View();
};
