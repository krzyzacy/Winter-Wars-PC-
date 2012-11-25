#include "Player_View.h"
#include "Player.h"

#include <zenilib.h>

using namespace Zeni;

Player_View::Player_View(const Player *p) :
	player(p)
{
	
}
	
Player_View::~Player_View()
{

}

void Player_View::set_camera(const Point2f &topLeft, const Point2f &bottomRight)
{
	get_Video().set_3d_view(player->get_camera(), std::make_pair(topLeft, bottomRight));
}

void Player_View::render_hud(const Point2f &topLeft, const Point2f &bottomRight)
{
	get_Video().set_2d(std::make_pair(topLeft,bottomRight),true);

	get_Fonts()["cat"].render_text("test",topLeft,Color(0x99660099));

}