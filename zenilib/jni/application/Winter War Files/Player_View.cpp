#include "Player_View.h"
#include "Player.h"
#include "Structure.h"
#include "World.h"
#include "Game_Model.h"
#include "Tile.h"
#include "string.h"
#include <math.h>

#include <zenilib.h>
#include "Structure.h"

#define PI 3.1415926

using namespace Zeni;

Player_View::Player_View(const Player *p) :
	player(p)
{
	
}
	
Player_View::~Player_View()
{

}

void scaled_render_text(const Zeni::String text, const Zeni::Point3f &position, const Zeni::Color &color, float range){
	float ratio = 1.0f;
	float msglength = get_Fonts()["system_36_800x600"].get_text_width(text);

	while(msglength > range){
		msglength *= 0.9f;
		ratio *= 0.9f;
	}

	get_Fonts()["system_36_800x600"].render_text(text ,position, Vector3f(ratio,0,0), Vector3f(0,ratio,0), color);
}

void Player_View::set_camera(const Point2f &topLeft, const Point2f &bottomRight)
{
	get_Video().set_3d_view(player->get_camera(), std::make_pair(topLeft, bottomRight));
}

void Player_View::render_hud(const Point2f &topLeft, const Point2f &bottomRight)
{
//	get_Video().set_2d(std::make_pair(topLeft,bottomRight), true);

	float unit_px = (bottomRight.x - topLeft.x) / 960.0f;
	
	std::string gender = "Girl";
	std::string team = "Blue";
	std::string status = "Regular";
	
	if(player->get_gender() == "boy")
		gender = "Boy";
	if(player->get_gender() == "girl")
		gender = "Girl";

	if(player->get_team()->get_Team_Index() == 1)
		team = "Green";
	else if(player->get_team()->get_Team_Index() == 2)
		team = "Red";
	else if(player->get_team()->get_Team_Index() == 3)
		team = "Blue";
	else if(player->get_team()->get_Team_Index() == 4)
		team = "Orange";

	if(player->is_player_KO()){
		status = "Fainted";
	}
	else if(player->get_hit_timer() >= 1.0f){
		status = "Hit";

		if(player->get_hit_timer() >= 1.7f)
			render_image("snow_hit_3",topLeft,Point2f(topLeft.x + unit_px * 1024, topLeft.y + unit_px * 1024));
		else if(player->get_hit_timer() >= 1.4f)
			render_image("snow_hit_2",topLeft,Point2f(topLeft.x + unit_px * 1024, topLeft.y + unit_px * 1024));
		else
			render_image("snow_hit_1",topLeft,Point2f(topLeft.x + unit_px * 1024, topLeft.y + unit_px * 1024));
	}
	else if(player->is_packing()){
		status = "Packing";
	}
	else if(player->get_throw_timer() >= 1.0f){
		status = "Throwing";
	}
	else if(player->get_Health() <= 30.0f){
		status = "Tired";
	}


	//if()

	render_image("AvartarFrame",topLeft,Point2f(topLeft.x + unit_px * 200, topLeft.y + unit_px * 200));
	render_image("BuildingFrame",Point2f(bottomRight.x - unit_px * 270, topLeft.y),Point2f(bottomRight.x, topLeft.y + unit_px * 270));
	render_image("PriceBox",Point2f(bottomRight.x - unit_px * 100, topLeft.y + unit_px * 5),Point2f(bottomRight.x - unit_px * 5, topLeft.y + unit_px * 100));
	render_image((Zeni::String)gender+(Zeni::String)team+(Zeni::String)status,Point2f(topLeft.x + unit_px * 10, topLeft.y + unit_px * 10), Point2f(topLeft.x + unit_px * 120, topLeft.y + unit_px * 120));
	//render_image("IceBlock",Point2f(topLeft.x + unit_px * 410, topLeft.y + unit_px * 5), Point2f(topLeft.x + unit_px * 450, topLeft.y + unit_px * 45));
	render_image("coin",Point2f(bottomRight.x - unit_px * 93, topLeft.y + unit_px * 12),Point2f(bottomRight.x - unit_px * 69, topLeft.y + unit_px * 36));

	scaled_render_text(itoa((int)player->get_Team_Blocks()), Point3f(bottomRight.x - unit_px * 65, topLeft.y + unit_px * 10, 0), Color(0xCCFF1111), (bottomRight.x - topLeft.x) * 0.05);
	
	render_image("Heart",Point2f(topLeft.x + unit_px * 180, topLeft.y + unit_px * 5), Point2f(topLeft.x + unit_px * 220, topLeft.y + unit_px * 45));
	render_image("Snowball",Point2f(topLeft.x + unit_px * 515, topLeft.y + unit_px * 5), Point2f(topLeft.x + unit_px * 555, topLeft.y + unit_px * 45));

	

	const Point2f p_ul(topLeft.x + unit_px * 560, topLeft.y + unit_px * 15);
	const Point2f p_ll(topLeft.x + unit_px * 560, topLeft.y + unit_px * 35);
	const Point2f p_lr(topLeft.x + unit_px * (560 + player->get_Snow() / (Max_Snow_Amount/150)), topLeft.y + unit_px * 35);
	const Point2f p_ur(topLeft.x + unit_px * (560 + player->get_Snow() / (Max_Snow_Amount/150)), topLeft.y + unit_px * 15);

	Colors &cr = get_Colors();

	Vertex2f_Color snowbar_ul(p_ul,cr["white"]);
	Vertex2f_Color snowbar_ll(p_ll,cr["white"]);
	Vertex2f_Color snowbar_lr(p_lr,cr["lightblue"]);
	Vertex2f_Color snowbar_ur(p_ur,cr["lightblue"]);

	Quadrilateral<Vertex2f_Color> snowbar(snowbar_ul, snowbar_ll, snowbar_lr, snowbar_ur);

	get_Video().render(snowbar);

	const Point2f h_ul(topLeft.x + unit_px * 225, topLeft.y + unit_px * 15);
	const Point2f h_ll(topLeft.x + unit_px * 225, topLeft.y + unit_px * 35);
	const Point2f h_lr(topLeft.x + unit_px * (225 + player->get_Health() / (Max_Player_Health/150)), topLeft.y + unit_px * 35);
	const Point2f h_ur(topLeft.x + unit_px * (225 + player->get_Health() / (Max_Player_Health/150)), topLeft.y + unit_px * 15);

	Vertex2f_Color healthbar_ul(h_ul,cr["red"]);
	Vertex2f_Color healthbar_ll(h_ll,cr["red"]);
	Vertex2f_Color healthbar_lr(h_lr,cr["green"]);
	Vertex2f_Color healthbar_ur(h_ur,cr["green"]);

	Quadrilateral<Vertex2f_Color> healthbar(healthbar_ul, healthbar_ll, healthbar_lr, healthbar_ur);

	get_Video().render(healthbar);


	//Hey Sen, I added a get_build_view for when the build menu should be up
	//Also theres a get_stick_choice() that returns the angle the joystick is making
	//If you want, you can use that you show which building the player is selecting when it's open

	if( /*player->get_team()->Is_Tree_Claimed()*/ Game_Model::get().time_till_win() < time_to_win_c ){
		render_tree_claimed(topLeft, bottomRight);
	}

	if( player->get_time_until_respawn() < 6.0f){
		render_death(topLeft, bottomRight);
	}
	else{

		if( player->get_mini_view() ){
			//render_death(topLeft, bottomRight);
			render_minimap(topLeft, bottomRight, gender+team+status );
		}
		else if( player->get_build_view() ){
			//render_tree_claimed(topLeft, bottomRight);
		}
		else{ // redical
			Point2f r_center;
			r_center.x = topLeft.x + unit_px * 480;
			r_center.y = topLeft.y + unit_px * 300;

			float scale = 20.0f;
			if(player->get_packing_timer() >= 1.0f)
				scale = scale * player->get_packing_timer() * player->get_packing_timer();

			render_image("BuildManu2D",Point2f(r_center.x - scale, r_center.y - scale), Point2f(r_center.x + scale, r_center.y + scale));
		}

		render_build(topLeft, bottomRight);
	}

	if( player->has_message() )
		render_message(topLeft, bottomRight, player->get_message());




	//get_Fonts()["system_36_800x600"].render_text("Scale: " + itoa(bottomRight.x - topLeft.x - unit_px * 180) ,Point3f(topLeft.x + unit_px * 100, bottomRight.y - unit_px * 75, 0), Vector3f(0.8,0,0), Vector3f(0,0.8,0), Color(0xFF000000));	

	

}

void Player_View::render_minimap(const Point2f &topLeft, const Point2f &bottomRight, std::string avartar){
	float unit_px = (bottomRight.x - topLeft.x) / 960.0f;
	float ratio = 4.85f;

	Point2f tile_pos(Game_Model::get().get_World()->get_tile(0, 0)->get_top_center().x, Game_Model::get().get_World()->get_tile(0, 0)->get_top_center().y);

	scaled_render_text("<|Espionage Center|>", Point3f(topLeft.x + unit_px * 320, topLeft.y + unit_px * 70, 0), Color(0x99FF0000), (bottomRight.x - topLeft.x) * 0.35);
	
	//get_Fonts()["system_36_800x600"].render_text("<|Espionage Center|>" ,Point2f(320, 70),Color(0x99FF0000));
	//render_image("Heart",Point2f(topLeft.x + tile_pos.x, topLeft.y + tile_pos.y),Point2f(topLeft.x + tile_pos.x + unit_px * 50, topLeft.y + tile_pos.y + unit_px * 50));

	for(int row = 0; row < Game_Model::get().get_World()->get_height(); row++){
		for(int col = 0; col < Game_Model::get().get_World()->get_width(); col++){
			
			Point2f tile_pos(Game_Model::get().get_World()->get_tile(row, col)->get_top_center().x, Game_Model::get().get_World()->get_tile(row, col)->get_top_center().y);

			String tile_name = "Tile2D";

			if(row == 0 || col == 0 || row == Game_Model::get().get_World()->get_height() - 1 || col == Game_Model::get().get_World()->get_width() - 1){
				tile_name += "Cliff";
			}
			else if(row == 6 && col == 7){
				tile_name += "ChristmasTree";
			}
			else{
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
			}

			tile_pos.x /= ratio;
			tile_pos.y /= ratio;

			render_image(tile_name,Point2f(topLeft.x + tile_pos.x * unit_px + unit_px * 200, topLeft.y + tile_pos.y * unit_px + unit_px * 90),Point2f(topLeft.x + tile_pos.x * unit_px + unit_px * 257, topLeft.y + tile_pos.y * unit_px + unit_px * 147));
		
		}
	}

	Point2f player_pos(player->get_camera().position.x / ratio,player->get_camera().position.y / ratio);

	float angle = atan(player->get_camera().get_forward().x / player->get_camera().get_forward().y);
	if(player->get_camera().get_forward().y < 0)
		angle += PI;

	render_image((Zeni::String)avartar,Point2f(topLeft.x + player_pos.x * unit_px + unit_px * 195.0f, topLeft.y + player_pos.y * unit_px + 80.0f * unit_px),
				Point2f(topLeft.x + player_pos.x * unit_px + unit_px * 235, topLeft.y + player_pos.y * unit_px + unit_px * 120), 
				angle , 1.0f, Point2f(topLeft.x + player_pos.x * unit_px + unit_px * 215, topLeft.y + player_pos.y * unit_px + unit_px * 100) );

}

void Player_View::render_build(const Point2f &topLeft, const Point2f &bottomRight){
	float unit_px = (bottomRight.x - topLeft.x) / 960.0f;

	//render_image("BuildManu2D",Point2f(topLeft.x + unit_px * 380, topLeft.y + unit_px * 200), Point2f(topLeft.x + unit_px * 580, topLeft.y + unit_px * 400));

	float stick_theta = player->get_stick_choice();
	Structure_Type choice = player->get_current_choice();

	//Joystick points Left
	//if(	stick_theta > Global::three_pi_over_two + Global::pi/4 ||
	//		stick_theta < Global::pi/4){
	if(choice == SNOWMAN)	{
		//render_image("Fortress2D",Point2f(topLeft.x + unit_px * 430, topLeft.y + unit_px * 395), Point2f(topLeft.x + unit_px * 530, topLeft.y + unit_px * 495));
		//render_image("Factory2D",Point2f(topLeft.x + unit_px * 575, topLeft.y + unit_px * 250), Point2f(topLeft.x + unit_px * 675, topLeft.y + unit_px * 350));
		//render_image("HealingPool2D",Point2f(topLeft.x + unit_px * 430, topLeft.y + unit_px * 105), Point2f(topLeft.x + unit_px * 530, topLeft.y + unit_px * 205));
		//render_image("Snowman2D",Point2f(topLeft.x + unit_px * 225, topLeft.y + unit_px * 220), Point2f(topLeft.x + unit_px * 385, topLeft.y + unit_px * 380));

		render_image("HealingPool2D",Point2f(bottomRight.x - unit_px * 175, topLeft.y + unit_px * 10),Point2f(bottomRight.x - unit_px * 125, topLeft.y + unit_px * 60));
		render_image("Fortress2D",Point2f(bottomRight.x - unit_px * 60, topLeft.y + unit_px * 125),Point2f(bottomRight.x - unit_px * 10, topLeft.y + unit_px * 175));
		render_image("Snowman2D",Point2f(bottomRight.x - unit_px * 158, topLeft.y + unit_px * 32),Point2f(bottomRight.x - unit_px * 32, topLeft.y + unit_px * 158));

		scaled_render_text(itoa(Build_Cost[1]), Point3f(bottomRight.x - unit_px * 120, topLeft.y + unit_px * 152, 0), Color(0xCCFF1111), (bottomRight.x - topLeft.x) * 0.05 );
		//render_image("Snowman2D",Point2f(topLeft.x + unit_px * 500, topLeft.y + unit_px * 1), Point2f(topLeft.x + unit_px * 800, topLeft.y + unit_px * 301));
	}

	//Down
	//if(stick_theta < Global::pi - Global::pi/4 &&
	//	stick_theta > Global::pi/4){
	if(choice == FORT)	{
		//render_image("Snowman2D",Point2f(topLeft.x + unit_px * 285, topLeft.y + unit_px * 250), Point2f(topLeft.x + unit_px * 385, topLeft.y + unit_px * 350));
		//render_image("Factory2D",Point2f(topLeft.x + unit_px * 575, topLeft.y + unit_px * 250), Point2f(topLeft.x + unit_px * 675, topLeft.y + unit_px * 350));
		//render_image("HealingPool2D",Point2f(topLeft.x + unit_px * 430, topLeft.y + unit_px * 105), Point2f(topLeft.x + unit_px * 530, topLeft.y + unit_px * 205));
		//render_image("Fortress2D",Point2f(topLeft.x + unit_px * 400, topLeft.y + unit_px * 395), Point2f(topLeft.x + unit_px * 560, topLeft.y + unit_px * 555));

		render_image("Snowman2D",Point2f(bottomRight.x - unit_px * 175, topLeft.y + unit_px * 10),Point2f(bottomRight.x - unit_px * 125, topLeft.y + unit_px * 60));
		render_image("Factory2D",Point2f(bottomRight.x - unit_px * 60, topLeft.y + unit_px * 125),Point2f(bottomRight.x - unit_px * 10, topLeft.y + unit_px * 175));
		render_image("Fortress2D",Point2f(bottomRight.x - unit_px * 158, topLeft.y + unit_px * 32),Point2f(bottomRight.x - unit_px * 32, topLeft.y + unit_px * 158));

		scaled_render_text(itoa(Build_Cost[2]), Point3f(bottomRight.x - unit_px * 120, topLeft.y + unit_px * 152, 0), Color(0xCCFF1111), (bottomRight.x - topLeft.x) * 0.05 );
		//render_image("Fortress2D",Point2f(topLeft.x + unit_px * 500, topLeft.y + unit_px * 1), Point2f(topLeft.x + unit_px * 800, topLeft.y + unit_px * 301));
	}

	//Right
	//if(stick_theta < Global::pi + Global::pi/4 &&
	//	stick_theta > Global::pi_over_two + Global::pi/4){
	if(choice == SNOW_FACTORY)	{
		//render_image("Snowman2D",Point2f(topLeft.x + unit_px * 285, topLeft.y + unit_px * 250), Point2f(topLeft.x + unit_px * 385, topLeft.y + unit_px * 350));
		//render_image("Fortress2D",Point2f(topLeft.x + unit_px * 430, topLeft.y + unit_px * 395), Point2f(topLeft.x + unit_px * 530, topLeft.y + unit_px * 495));
		//render_image("HealingPool2D",Point2f(topLeft.x + unit_px * 430, topLeft.y + unit_px * 105), Point2f(topLeft.x + unit_px * 530, topLeft.y + unit_px * 205));
		//render_image("Factory2D",Point2f(topLeft.x + unit_px * 575, topLeft.y + unit_px * 220), Point2f(topLeft.x + unit_px * 735, topLeft.y + unit_px * 380));

		render_image("Fortress2D",Point2f(bottomRight.x - unit_px * 175, topLeft.y + unit_px * 10),Point2f(bottomRight.x - unit_px * 125, topLeft.y + unit_px * 60));
		render_image("HealingPool2D",Point2f(bottomRight.x - unit_px * 60, topLeft.y + unit_px * 125),Point2f(bottomRight.x - unit_px * 10, topLeft.y + unit_px * 175));
		render_image("Factory2D",Point2f(bottomRight.x - unit_px * 158, topLeft.y + unit_px * 32),Point2f(bottomRight.x - unit_px * 32, topLeft.y + unit_px * 158));

		scaled_render_text(itoa(Build_Cost[3]), Point3f(bottomRight.x - unit_px * 120, topLeft.y + unit_px * 152, 0), Color(0xCCFF1111), (bottomRight.x - topLeft.x) * 0.05 );
		//render_image("Factory2D",Point2f(topLeft.x + unit_px * 500, topLeft.y + unit_px * 1), Point2f(topLeft.x + unit_px * 800, topLeft.y + unit_px * 301));
	}

	//Up
	//if(stick_theta < Global::three_pi_over_two + Global::pi/4 && 
	//	stick_theta > Global::three_pi_over_two - Global::pi/4){
	if(choice == HEALING_POOL)	{
		//render_image("Snowman2D",Point2f(topLeft.x + unit_px * 285, topLeft.y + unit_px * 250), Point2f(topLeft.x + unit_px * 385, topLeft.y + unit_px * 350));
		//render_image("Fortress2D",Point2f(topLeft.x + unit_px * 430, topLeft.y + unit_px * 395), Point2f(topLeft.x + unit_px * 530, topLeft.y + unit_px * 495));
		//render_image("Factory2D",Point2f(topLeft.x + unit_px * 575, topLeft.y + unit_px * 250), Point2f(topLeft.x + unit_px * 675, topLeft.y + unit_px * 350));
		//render_image("HealingPool2D",Point2f(topLeft.x + unit_px * 400, topLeft.y + unit_px * 45), Point2f(topLeft.x + unit_px * 560, topLeft.y + unit_px * 205));

		render_image("Factory2D",Point2f(bottomRight.x - unit_px * 175, topLeft.y + unit_px * 10),Point2f(bottomRight.x - unit_px * 125, topLeft.y + unit_px * 60));
		render_image("Snowman2D",Point2f(bottomRight.x - unit_px * 60, topLeft.y + unit_px * 125),Point2f(bottomRight.x - unit_px * 10, topLeft.y + unit_px * 175));
		render_image("HealingPool2D",Point2f(bottomRight.x - unit_px * 158, topLeft.y + unit_px * 32),Point2f(bottomRight.x - unit_px * 32, topLeft.y + unit_px * 158));

		scaled_render_text(itoa(Build_Cost[4]), Point3f(bottomRight.x - unit_px * 120, topLeft.y + unit_px * 152, 0), Color(0xCCFF1111), (bottomRight.x - topLeft.x) * 0.05 );

		//render_image("HealingPool2D",Point2f(topLeft.x + unit_px * 500, topLeft.y + unit_px * 1), Point2f(topLeft.x + unit_px * 800, topLeft.y + unit_px * 301));
	}

}
void Player_View::render_death(const Point2f &topLeft, const Point2f &bottomRight){
	float unit_px = (bottomRight.x - topLeft.x) / 960.0f;


	render_image("Death",topLeft,Point2f(topLeft.x + unit_px * 1024, topLeft.y + unit_px * 1024));
	//render_image("reaper",Point2f(topLeft.x + unit_px * 350, topLeft.y + unit_px * 350),Point2f(topLeft.x + unit_px * 650, topLeft.y + unit_px * 650));
	get_Fonts()["system_36_800x600"].render_text("...Respawn in " + itoa((int)player->get_time_until_respawn()) + " seconds..." ,Point2f(topLeft.x + unit_px * 280, topLeft.y + unit_px * 400), Color(0x99FF1111));

}

void Player_View::render_message(const Point2f &topLeft, const Point2f &bottomRight, const Zeni::String message){
	float unit_px = (bottomRight.x - topLeft.x) / 960.0f;

	render_image("message_bar",Point2f(topLeft.x, bottomRight.y - unit_px * 280),bottomRight);

	scaled_render_text(message, Point3f(topLeft.x + unit_px * 100, bottomRight.y - unit_px * 75, 0), Color(0xFF000000), bottomRight.x - topLeft.x - unit_px * 180);


}

void Player_View::render_tree_claimed(const Point2f &topLeft, const Point2f &bottomRight){
	float unit_px = (bottomRight.x - topLeft.x) / 960.0f;

	Colors &cr = get_Colors();
	const Color blk = cr[player->get_team()->get_name()];

	render_image("Alert_" + Game_Model::get().get_team(Game_Model::get().get_World()->get_center_Tile()->get_team() - 1)->get_name(),Point2f(topLeft.x + unit_px * 250, topLeft.y + unit_px * 120),Point2f(topLeft.x + unit_px * 710, topLeft.y + unit_px * 580));
	get_Fonts()["cat"].render_text(itoa((int)Game_Model::get().time_till_win()) ,Point2f(topLeft.x + unit_px * 440, topLeft.y + unit_px * 50), Color(0xFFFF0000));

}

