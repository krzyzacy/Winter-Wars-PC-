#pragma once

#include "Player_View.h"

class Player;

class Player_Deathmatch_View : public Player_View
{
public:
	Player_Deathmatch_View(Player* p);
	virtual ~Player_Deathmatch_View();

	void render_hud(const Zeni::Point2f &topLeft, const Zeni::Point2f &bottomRight) override;
	void render_minimap(const Zeni::Point2f &topLeft, const Zeni::Point2f &bottomRight, const std::string avartar) override;
};
