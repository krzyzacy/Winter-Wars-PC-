#include "Player_Deathmatch_View.h"

Player_Deathmatch_View::Player_Deathmatch_View(Player* p) : Player_View(p)
{ }

Player_Deathmatch_View::~Player_Deathmatch_View() 
{ }

void Player_Deathmatch_View::render_hud(const Zeni::Point2f &topLeft, const Zeni::Point2f &bottomRight)
{
	Player_View::render_hud(topLeft, bottomRight);
}

void Player_Deathmatch_View::render_minimap(const Zeni::Point2f &topLeft, const Zeni::Point2f &bottomRight, const std::string avatar)
{
	Player_View::render_minimap(topLeft, bottomRight, avatar);
}
