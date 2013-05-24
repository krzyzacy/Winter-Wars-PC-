#pragma once

#include "Player_View.h"

class Player;

class Player_Claim_Tree_View : public Player_View
{
public:
	Player_Claim_Tree_View(Player* p);
	virtual ~Player_Claim_Tree_View();

	void render_hud(const Zeni::Point2f &topLeft, const Zeni::Point2f &bottomRight) override;

};
