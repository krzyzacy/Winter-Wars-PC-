#include "Player_Deathmatch_View.h"
#include "Player_View.h"
#include "Utility.h"
#include "Player.h"
#include "Game_Model.h"
#include "Team.h"

#include <zenilib.h>

using namespace Zeni;

Player_Deathmatch_View::Player_Deathmatch_View(Player* p) : Player_View(p)
{ }

Player_Deathmatch_View::~Player_Deathmatch_View() 
{ }

void Player_Deathmatch_View::render_hud(const Zeni::Point2f &topLeft, const Zeni::Point2f &bottomRight)
{
	float unit_px = (bottomRight.x - topLeft.x) / 960.0f;


	Player_View::render_hud(topLeft, bottomRight);
	Zeni::Point2f bottomLeft(topLeft.x, bottomRight.y);
	int team_kills = get_player()->get_team()->get_Player_Kills();
	int time_left = Game_Model::get().get_time_left();
	const Color &team_color = get_Colors()[get_player()->get_team()->get_name()];

	render_image("PriceBox", Point2f(bottomLeft.x, bottomLeft.y - unit_px * 75), Point2f(bottomLeft.x + unit_px * 96, bottomLeft.y + unit_px * 117));
	scaled_render_text("Score:    " + itoa(team_kills), Point3f(bottomLeft.x + unit_px * 8, bottomLeft.y - unit_px * 55, 0), team_color, unit_px * 75);
	scaled_render_text("Time:  " + make_time_string(int(time_left)), Point3f(bottomLeft.x + unit_px * 8, bottomLeft.y - unit_px * 33, 0), team_color, unit_px * 75);
}


void Player_Deathmatch_View::render_minimap(const Zeni::Point2f &topLeft, const Zeni::Point2f &bottomRight, const std::string avatar)
{
	Player_View::render_minimap(topLeft, bottomRight, avatar);
}
