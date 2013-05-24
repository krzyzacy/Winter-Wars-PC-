#include "Player_Claim_Tree_View.h"
#include "Player.h"
#include <zenilib.h>
#include "Zeni/Joysticks.h"

using namespace std;
using namespace Zeni;

Player_Claim_Tree_View::Player_Claim_Tree_View(Player* p): Player_View(p)
{ }

Player_Claim_Tree_View::~Player_Claim_Tree_View()
{ }

void Player_Claim_Tree_View::render_hud(const Zeni::Point2f &topLeft, const Zeni::Point2f &bottomRight)
{
	Player_View::render_hud(topLeft, bottomRight);
	float unit_px = (bottomRight.x - topLeft.x) / 960.0f;


	if(!get_Joysticks().is_xinput_connected(0))
		render_image("BuildingFrameEmpty",Point2f(bottomRight.x - unit_px * 270, topLeft.y),Point2f(bottomRight.x, topLeft.y + unit_px * 270));
	else render_image("BuildingFrame",Point2f(bottomRight.x - unit_px * 270, topLeft.y),Point2f(bottomRight.x, topLeft.y + unit_px * 270));
	render_image("PriceBox",Point2f(bottomRight.x - unit_px * 100, topLeft.y + unit_px * 5),Point2f(bottomRight.x - unit_px * 5, topLeft.y + unit_px * 120));
	//render_image("IceBlock",Point2f(topLeft.x + unit_px * 410, topLeft.y + unit_px * 5), Point2f(topLeft.x + unit_px * 450, topLeft.y + unit_px * 45));
	render_image("coin",Point2f(bottomRight.x - unit_px * 93, topLeft.y + unit_px * 12),Point2f(bottomRight.x - unit_px * 69, topLeft.y + unit_px * 36));

	scaled_render_text_height(itoa((int)get_player()->get_Team_Blocks()), Point3f(bottomRight.x - unit_px * 65, topLeft.y + unit_px * 10, 0), Color(0xCCFF1111), unit_px * 30);
	scaled_render_text_height("+" + itoa((int)get_player()->get_Team_Resource_Rate()), Point3f(bottomRight.x - unit_px * 65, topLeft.y + unit_px * 26, 0), Color(0xCCFF1111), unit_px * 25);
	if( get_player()->get_time_until_respawn() >= Respawn_Time){
		render_build(topLeft, bottomRight);
	}
	scaled_render_text_height(itoa(get_Joysticks().get_num_joysticks()), Point3f(bottomRight.x - unit_px * 65, topLeft.y + unit_px * 60, 0), Color(0xCCFF1111), unit_px * 30);
}
