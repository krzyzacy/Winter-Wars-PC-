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

void Player_View::set_camera()
{
	get_Video().set_3d_view(player->get_camera(), std::make_pair(Point2i(0,0), Point2i(800,600)));
}