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
//	get_Video().set_2d(std::make_pair(topLeft,bottomRight), true);

	get_Fonts()["cat"].render_text("TL.x = " + itoa(topLeft.x) + " BR.x = " + itoa(bottomRight.x) ,topLeft,Color(0x99660099));

	float unit_px = (bottomRight.x - topLeft.x) / 960.0f;

	render_image("Frame",topLeft,Point2f(topLeft.x + unit_px * 500, topLeft.y + unit_px * 500));
	render_image("BoyBlueRegular",Point2f(topLeft.x + unit_px * 15, topLeft.y + unit_px * 10), Point2f(topLeft.x + unit_px * 105, topLeft.y + unit_px * 100));
	render_image("IceBlock",Point2f(topLeft.x + unit_px * 15, topLeft.y + unit_px * 95), Point2f(topLeft.x + unit_px * 45, topLeft.y + unit_px * 125));
	render_image("Heart",Point2f(topLeft.x + unit_px * 126, topLeft.y + unit_px * 25), Point2f(topLeft.x + unit_px * 171, topLeft.y + unit_px * 70));
	render_image("Snowball",Point2f(topLeft.x + unit_px * 130, topLeft.y + unit_px * 85), Point2f(topLeft.x + unit_px * 170, topLeft.y + unit_px * 125));

	const Point2f p_ul(topLeft.x + unit_px * 175, topLeft.y + unit_px * 95);
	const Point2f p_ll(topLeft.x + unit_px * 175, topLeft.y + unit_px * 125);
	//Hey Sen, I messed with this, trying to incorporate constants from Player, Seems sort of not adjustable the way I did it
	//So if you come up with a better way awesome
	const Point2f p_lr(topLeft.x + unit_px * (175 + player->get_Snow() / (Max_Snow_Amount/150)), topLeft.y + unit_px * 125);
	const Point2f p_ur(topLeft.x + unit_px * (175 + player->get_Snow() / (Max_Snow_Amount/150)), topLeft.y + unit_px * 95);

	Colors &cr = get_Colors();

	Vertex2f_Color ul(p_ul,cr["red"]);
	Vertex2f_Color ll(p_ll,cr["red"]);
	Vertex2f_Color lr(p_lr,cr["red"]);
	Vertex2f_Color ur(p_ur,cr["red"]);

	Quadrilateral<Vertex2f_Color> quad(ul, ll, lr, ur);

	get_Video().render(quad);

}