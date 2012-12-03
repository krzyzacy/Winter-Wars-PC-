#include "Player_View.h"
#include "Player.h"
#include "World.h"
#include "Game_Model.h"
#include "Tile.h"
#include "string.h"

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

	float unit_px = (bottomRight.x - topLeft.x) / 960.0f;
	get_Fonts()["resource"].render_text("Player.lookat.x = " + ftoa(player->get_camera().get_forward().x) + "Player.lookat.y = " + ftoa(player->get_camera().get_forward().y) ,Point2f(topLeft.x + unit_px * 5, topLeft.y + unit_px * 250),Color(0x99660099));
	Tile* testtile = Game_Model::get().get_World()->player_is_looking_at(player->get_camera().position,player->get_camera().get_forward());
	Tile* curtile = Game_Model::get().get_World()->get_tile(player->get_camera().position);
	
	if(testtile != NULL && curtile != NULL){
		get_Fonts()["resource"].render_text("stand.row = " + itoa(curtile->get_row()) + " stand.col = " + itoa(curtile->get_col()) ,Point2f(topLeft.x + unit_px * 5, topLeft.y + unit_px * 400),Color(0x99660099));
		get_Fonts()["resource"].render_text("lookat.row = " + itoa(testtile->get_row()) + " lookat.col = " + itoa(testtile->get_col()) ,Point2f(topLeft.x + unit_px * 5, topLeft.y + unit_px * 450),Color(0x99660099));
	}
	else{
		get_Fonts()["resource"].render_text(" out of bound! " ,Point2f(topLeft.x + unit_px * 5, topLeft.y + unit_px * 450),Color(0x99660099));
	}

	render_image("Frame",topLeft,Point2f(topLeft.x + unit_px * 500, topLeft.y + unit_px * 500));
	render_image("BoyBlueRegular",Point2f(topLeft.x + unit_px * 15, topLeft.y + unit_px * 10), Point2f(topLeft.x + unit_px * 105, topLeft.y + unit_px * 100));
	render_image("IceBlock",Point2f(topLeft.x + unit_px * 15, topLeft.y + unit_px * 95), Point2f(topLeft.x + unit_px * 45, topLeft.y + unit_px * 125));
	render_image("Heart",Point2f(topLeft.x + unit_px * 126, topLeft.y + unit_px * 25), Point2f(topLeft.x + unit_px * 171, topLeft.y + unit_px * 70));
	render_image("Snowball",Point2f(topLeft.x + unit_px * 130, topLeft.y + unit_px * 85), Point2f(topLeft.x + unit_px * 170, topLeft.y + unit_px * 125));

	get_Fonts()["resource"].render_text(itoa((int)player->get_Team_Blocks()), Point2f(topLeft.x + unit_px * 48, topLeft.y + unit_px * 95),Color(0x99220022));

	const Point2f p_ul(topLeft.x + unit_px * 175, topLeft.y + unit_px * 95);
	const Point2f p_ll(topLeft.x + unit_px * 175, topLeft.y + unit_px * 125);
	const Point2f p_lr(topLeft.x + unit_px * (175 + player->get_Snow() / (Max_Snow_Amount/150)), topLeft.y + unit_px * 125);
	const Point2f p_ur(topLeft.x + unit_px * (175 + player->get_Snow() / (Max_Snow_Amount/150)), topLeft.y + unit_px * 95);

	Colors &cr = get_Colors();

	Vertex2f_Color snowbar_ul(p_ul,cr["blue"]);
	Vertex2f_Color snowbar_ll(p_ll,cr["blue"]);
	Vertex2f_Color snowbar_lr(p_lr,cr["white"]);
	Vertex2f_Color snowbar_ur(p_ur,cr["white"]);

	Quadrilateral<Vertex2f_Color> snowbar(snowbar_ul, snowbar_ll, snowbar_lr, snowbar_ur);

	get_Video().render(snowbar);

	const Point2f h_ul(topLeft.x + unit_px * 175, topLeft.y + unit_px * 40);
	const Point2f h_ll(topLeft.x + unit_px * 175, topLeft.y + unit_px * 70);
	const Point2f h_lr(topLeft.x + unit_px * (175 + player->get_Health() / (Max_Player_Health/150)), topLeft.y + unit_px * 70);
	const Point2f h_ur(topLeft.x + unit_px * (175 + player->get_Health() / (Max_Player_Health/150)), topLeft.y + unit_px * 40);

	Vertex2f_Color healthbar_ul(h_ul,cr["red"]);
	Vertex2f_Color healthbar_ll(h_ll,cr["red"]);
	Vertex2f_Color healthbar_lr(h_lr,cr["green"]);
	Vertex2f_Color healthbar_ur(h_ur,cr["green"]);

	Quadrilateral<Vertex2f_Color> healthbar(healthbar_ul, healthbar_ll, healthbar_lr, healthbar_ur);

	get_Video().render(healthbar);


	//Hey Sen, I added a get_build_view for when the build menu should be up
	//Also theres a get_stick_choice() that returns the angle the joystick is making
	//If you want, you can use that you show which building the player is selecting when it's open
	if( player->get_mini_view() ){
		render_minimap(topLeft, bottomRight);
	}

	if( player->get_build_view() ){
		render_build(topLeft, bottomRight);
	}

	render_image("BuildManu2D",Point2f(topLeft.x + unit_px * 460, topLeft.y + unit_px * 280), Point2f(topLeft.x + unit_px * 500, topLeft.y + unit_px * 320));

}

void Player_View::render_minimap(const Point2f &topLeft, const Point2f &bottomRight){
	float unit_px = (bottomRight.x - topLeft.x) / 960.0f;
	float ratio = 4.85f;

	Point2f tile_pos(Game_Model::get().get_World()->get_tile(0, 0)->get_top_center().x, Game_Model::get().get_World()->get_tile(0, 0)->get_top_center().y);
	get_Fonts()["resource"].render_text("<|Espionage Center|>" ,Point2f(topLeft.x + unit_px * 370, topLeft.y + unit_px * 30),Color(0x99660099));
	//render_image("Heart",Point2f(topLeft.x + tile_pos.x, topLeft.y + tile_pos.y),Point2f(topLeft.x + tile_pos.x + unit_px * 50, topLeft.y + tile_pos.y + unit_px * 50));

	for(int row = 0; row < Game_Model::get().get_World()->get_height(); row++){
		for(int col = 0; col < Game_Model::get().get_World()->get_width(); col++){
			
			Point2f tile_pos(Game_Model::get().get_World()->get_tile(row, col)->get_top_center().x, Game_Model::get().get_World()->get_tile(row, col)->get_top_center().y);

			String tile_name = "Tile2D";

			switch (Game_Model::get().get_World()->get_tile(row, col)->get_team()){
				case NEUTRAL:
					tile_name += "Neutral";
					break;
				case BLUE:
					tile_name += "Blue";
					break;
				case GREEN:
					tile_name += "Green";
					break;
				case RED:
					tile_name += "Red";
					break;
				case ORANGE:
					tile_name += "Orange";
					break;
				default:
					tile_name += "Regular";
					break;

			}

			tile_pos.x /= ratio;
			tile_pos.y /= ratio;

			render_image(tile_name,Point2f(topLeft.x + tile_pos.x * unit_px + unit_px * 200, topLeft.y + tile_pos.y * unit_px + unit_px * 50),Point2f(topLeft.x + tile_pos.x * unit_px + unit_px * 257, topLeft.y + tile_pos.y * unit_px + unit_px * 107));
		
		}
	}

	Point2f player_pos(player->get_camera().position.x / ratio,player->get_camera().position.y / ratio);
	render_image("Heart",Point2f(topLeft.x + player_pos.x * unit_px + unit_px * 180.0f, topLeft.y + player_pos.y * unit_px + 14.0f * unit_px),Point2f(topLeft.x + player_pos.x * unit_px + unit_px * 237, topLeft.y + player_pos.y * unit_px + unit_px * 71));

}

void Player_View::render_build(const Point2f &topLeft, const Point2f &bottomRight){
	float unit_px = (bottomRight.x - topLeft.x) / 960.0f;

	render_image("BuildManu2D",Point2f(topLeft.x + unit_px * 400, topLeft.y + unit_px * 220), Point2f(topLeft.x + unit_px * 560, topLeft.y + unit_px * 370));

	float stick_theta = player->get_stick_choice();

	//Joystick points Left
	if(	stick_theta > Global::three_pi_over_two + Global::pi/4 ||
			stick_theta < Global::pi/4){
		render_image("Fortress2D",Point2f(topLeft.x + unit_px * 450, topLeft.y + unit_px * 375), Point2f(topLeft.x + unit_px * 510, topLeft.y + unit_px * 435));
		render_image("Factory2D",Point2f(topLeft.x + unit_px * 555, topLeft.y + unit_px * 270), Point2f(topLeft.x + unit_px * 615, topLeft.y + unit_px * 330));
		render_image("HealingPool2D",Point2f(topLeft.x + unit_px * 450, topLeft.y + unit_px * 165), Point2f(topLeft.x + unit_px * 510, topLeft.y + unit_px * 225));
		render_image("Snowman2D",Point2f(topLeft.x + unit_px * 285, topLeft.y + unit_px * 240), Point2f(topLeft.x + unit_px * 405, topLeft.y + unit_px * 360));
	}

	//Down
	if(stick_theta < Global::pi - Global::pi/4 &&
		stick_theta > Global::pi/4){
		render_image("Snowman2D",Point2f(topLeft.x + unit_px * 345, topLeft.y + unit_px * 270), Point2f(topLeft.x + unit_px * 405, topLeft.y + unit_px * 330));
		render_image("Factory2D",Point2f(topLeft.x + unit_px * 555, topLeft.y + unit_px * 270), Point2f(topLeft.x + unit_px * 615, topLeft.y + unit_px * 330));
		render_image("HealingPool2D",Point2f(topLeft.x + unit_px * 450, topLeft.y + unit_px * 165), Point2f(topLeft.x + unit_px * 510, topLeft.y + unit_px * 225));
		render_image("Fortress2D",Point2f(topLeft.x + unit_px * 420, topLeft.y + unit_px * 375), Point2f(topLeft.x + unit_px * 540, topLeft.y + unit_px * 495));
	}

	//Right
	if(stick_theta < Global::pi + Global::pi/4 &&
		stick_theta > Global::pi_over_two + Global::pi/4){
		render_image("Snowman2D",Point2f(topLeft.x + unit_px * 345, topLeft.y + unit_px * 270), Point2f(topLeft.x + unit_px * 405, topLeft.y + unit_px * 330));
		render_image("Fortress2D",Point2f(topLeft.x + unit_px * 450, topLeft.y + unit_px * 375), Point2f(topLeft.x + unit_px * 510, topLeft.y + unit_px * 435));
		render_image("HealingPool2D",Point2f(topLeft.x + unit_px * 450, topLeft.y + unit_px * 165), Point2f(topLeft.x + unit_px * 510, topLeft.y + unit_px * 225));
		render_image("Factory2D",Point2f(topLeft.x + unit_px * 555, topLeft.y + unit_px * 240), Point2f(topLeft.x + unit_px * 675, topLeft.y + unit_px * 360));
	}

	//Up
	if(stick_theta < Global::three_pi_over_two + Global::pi/4 && 
		stick_theta > Global::three_pi_over_two - Global::pi/4){
		render_image("Snowman2D",Point2f(topLeft.x + unit_px * 345, topLeft.y + unit_px * 270), Point2f(topLeft.x + unit_px * 405, topLeft.y + unit_px * 330));
		render_image("Fortress2D",Point2f(topLeft.x + unit_px *450, topLeft.y + unit_px * 375), Point2f(topLeft.x + unit_px * 510, topLeft.y + unit_px * 435));
		render_image("Factory2D",Point2f(topLeft.x + unit_px * 555, topLeft.y + unit_px * 270), Point2f(topLeft.x + unit_px * 615, topLeft.y + unit_px * 330));
		render_image("HealingPool2D",Point2f(topLeft.x + unit_px * 420, topLeft.y + unit_px * 125), Point2f(topLeft.x + unit_px * 540, topLeft.y + unit_px * 225));
	}

}