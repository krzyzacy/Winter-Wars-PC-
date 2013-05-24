#include "Player.h"

#include "Game_Model.h"
#include "Snowball.h"
#include "Team.h"
#include "World.h"
#include "Tile.h"
#include "Object_factory.h"
#include "PlayerAnimator.h"
#include "PlayerAnimators.h"
#include "Event.h"

#include <zenilib.h>

using namespace std;
using namespace Zeni;

const int Player::player_ID_c = 1;
float turn_speed = 40;
float up_look_speed = 20;


const int num_tips = 13;
vector<String> tips;
/*{
	"Show the next tip by pressing (Y).",
	"Point at a tile in front of you and build with (X).",
	"You can only build structures next to your existing structures",
	"Building on soft snow will generate the most resource.",
	"Need health? Go to a pool - but only your pool!",
	"Destroy structures with snowballs.",
	"Forts are difficult to destroy.",
	"Ice tiles make you slip and don't give you resources when owned.",
	"Snowmen can protect your territory.",
	"Factories changes adjacent tiles to soft snow tiles.",
	"Structures become inactive if they aren't connected to your base.",
	"After a structure is inactive, you need to reconnect it, or it will be destroyed!",
	"Winter Wars >>> Halo" //funny
};*/


Player::Player(Team* team_, const std::string &gender_)
	: Elf(team_, gender_),
	cur_tip(0),
	m_camera(center, Quaternion(), 5.0f, 3000.0f),
	stick_theta(0.0f),
	mini_open(false), 
	build_open(false)
{
	//field of view in y
	m_camera.fov_rad = Zeni::Global::pi / 3.0f;
	m_camera.look_at(Game_Model::get().get_center_tile()->get_top_center());

	//rotation = m_camera.orientation + Quaternion(Global::pi_over_two*2.375, 0,0);
	rotation = m_camera.orientation + Quaternion(Global::pi_over_two + Global::pi_over_two/2, 0,0);
	//rotation = m_camera.orientation;

	//player_sound_test = new Zeni::Sound_Source(Zeni::get_Sounds()["meow"]);
	//rotation = m_camera.orientation + Quaternion(Global::pi_over_two, 0, 0);
	//rotation += Quaternion(Global::pi_over_two, 0,0);

}

Player::~Player(void)
{}

void Player::adjust_pitch(float phi) {
    const Quaternion backup = m_camera.orientation;
    const Vector3f backup_up = m_camera.get_up();

    m_camera.adjust_pitch(phi * up_look_speed * Game_Model::get().get_time_step());

    if(m_camera.get_up().k < 0.0f && backup_up.k >= 0.0f)
      m_camera.orientation = backup;
}

void Player::turn_left(float theta) {	
	//Vector3f Old = m_camera.get_forward().get_ij();
	float angle = theta * turn_speed * Game_Model::get().get_time_step();

	m_camera.turn_left_xy(angle);
	//rotation *= m_camera.orientation.Vector3f_to_Vector3f(m_camera.get_forward().get_ij(), Old);
	//rotation *= rotation.Axis_Angle(Vector3f(0,0,10) , angle);
	rotation *= rotation.Axis_Angle(Vector3f(0,0,1) , angle);
	//rotation = m_camera.orientation;
}

void Player::update(const float &time)	{
	Elf::update(time);

	m_camera.position = center;

	if(Player_Movement_Message_Ticker.seconds() > 0.5)
	{
		Player_Movement_Event(this);
		
		Player_Movement_Message_Ticker.reset();
		Player_Movement_Message_Ticker.start();
	}

	stats.save_to_history();
}

void Player::get_damaged(float damage)	{
	Elf::get_damaged(damage);
	if(health > 0)
		ShakeTime.start();
}

void Player::throw_ball()	{
	if(is_player_KO())
		return;
	
	if(current_radius <= 0)	{
		//if radius is 0, means out of snow, and therefore don't throw
		return;
	}

	Game_Model::get().play_snowballthrow();

	Snowball *sb = new Snowball(this, center+m_camera.get_forward(), 
									Vector3f(current_radius, current_radius,current_radius));
	sb->get_thrown(m_camera.get_forward());
	
	if (current_radius > max_snowball_size/2)
		stats.num_large_snowballs++;
	else
		stats.num_small_snowballs++;

	Game_Model::get().add_moveable(sb);

	Throw_Snowball_Event(this, center+m_camera.get_forward()
		, m_camera.get_forward(), current_radius);

	current_radius = 0;
	switch_state(THROW);
	stats.thrown++;

	throw_timer = 1.0f;
	packing_timer = 0.0f;
}

void Player::charge_ball()	{
	Elf::charge_ball();

		// not enough snow
	if(Snow_in_Pack <= 0) 	{
		add_message("Out of Ammo! Find SOFT SNOW and scoop some up (E).");
		Snow_in_Pack = 0;
	}
}

bool Player::create_building(Structure_Type Building)	{
	//Returns true if building was created, false if unable
		
	Tile *t = Game_Model::get().get_World()->player_is_looking_at(center, m_camera.get_forward());
	
	if(t->has_building() && t->get_building()->get_type() == Building)
		return false;
	
	
	//true if the player is trying to build on the tree
	if(t->has_building() && t->get_building()->get_type() == TREE)
		Building = TREE;

	try {
		if(myTeam->allowed_to_build_on_Tile(t) && myTeam->can_afford_building(Building))	{
			Build_Event(create_structure(Building, t, myTeam));
			return true;
		}

		//Checks if the tile can be built upon
		return false;
	}
	catch (Error &E)
	{
		add_message(E.msg, 20000);
		return false;
	}
}

void Player::Make_Building(bool Go)	{
	if(is_player_KO())	{
		Builder = REST;
		return;
	}
	
	switch(Builder)	{
	case REST:
		//Oay to build fire away
		if(!Go)
			return;

		if(create_building(Selection))	{
			stats.built++;
			Builder = RECHARGE_BUILD;
			BuildTime.start();
		}
		else
			Builder = REST;
		break;
	case RECHARGE_BUILD:
		if(BuildTime.seconds() >= Building_Recharge_Time)	{
			BuildTime.stop();
			BuildTime.reset();
			Builder = REST;
		}
		break;
	default:
		Builder = REST;
		break;
	}
}

void Player::off_map()
{
	center.x = backup.x;
	center.y = backup.y;
}

void Player::hit_tile()
{
	//Use math, get the family, determine which one you are closest too., 
	//Make a vector from that and push

	//OutputDebugString(("HIT TILE" + itoa(hit_count ++ ) + "\n").std_str().c_str());

	//Anit geting stuck measures
	//center.x = backup.x;
	//center.y = backup.y;

	Vector3f push_dir;
	Tile* OnT = Game_Model::get().get_World()->get_tile(center);
//	OutputDebugString(("CURRENT TILE       ROW: " + itoa(OnT->get_row()) + " COL: " + itoa(OnT->get_col() ) + "\n").std_str().c_str());

	list<Tile*> fam = Game_Model::get().get_World()->Get_Family(OnT);
	Tile* Closest = fam.front();
	Vector3f close_dist = Closest->get_structure_base() - center;
	close_dist.z = 0;
	for(list<Tile*>::iterator it = fam.begin(); it != fam.end(); ++it)	{
		Vector3f dist((*it)->get_structure_base() - center);
		dist.z = 0;

//		OutputDebugString(("***---PARSING TILE:  ROW: " + itoa((*it)->get_row()) + " COL: " + itoa((*it)->get_col() ) + "\n").std_str().c_str());
//		OutputDebugString(("***---PARSING DIST:  " + itoa(dist.magnitude()) + "\n").std_str().c_str());


		if(dist.magnitude() < close_dist.magnitude())	{
			close_dist = dist;
			Closest = (*it);
		}
	}
//	OutputDebugString(("PUSH AWAY FROM TILE ROW: " + itoa(Closest->get_row()) + " COL: " + itoa(Closest->get_col() ) + "\n").std_str().c_str());
	//push_away_from(Closest->get_structure_base(), 12.5);
	push_away_from(Closest->get_structure_base(), 25);
	
	//push_away_from(tile->get_top_center(), -15.0f);

	//center.x = backup.x;
	//center.y = backup.y;
	
}

void Player::on_ground()
{
	if(velocity.z < 0)
		velocity.z = 0;

	// set them on the ground
	center.z = Game_Model::get().get_World()->get_ground_height(center) + size.z/2 + 10.0f;
}









 void Player::calculate_movement(const Vector2f input_vel)	{
	 if(is_player_KO())
		return;

	 if(!allowed_to_calculate_movement)
		 return;
	//input_vel is joystick values, from 0 to 32768
	//if(mini_open)	{	//Mini-map is open stop moving
	//	velocity = Vector3f(0,0, velocity.z);
	//	return;
	//}

	//Set up, get Camera Vectors and create variables
	Vector3f POV_face = m_camera.get_forward().get_ij();
	POV_face.normalize();
	Vector3f POV_left = m_camera.get_left().get_ij();
	POV_left.normalize();
		//The new velocity
	Vector3f New_vel = velocity;
		//The maximum speed allowed, based on how far joystick is pushed
	//if(abs(input_vel.y) < 1000) POV_face = Vector3f();
	//if(abs(input_vel.x) < 1000) POV_left = Vector3f();


	//multiplication and it's effects if negative number??
	//Vector2f input_vel2 = input_vel;
	//input_vel2.normalize();
	//Vector3f Input_Target_Vel = POV_face * input_vel2.y + POV_left * input_vel2.x;
	Vector3f Input_Target_Vel = ( POV_face * (input_vel.y/Max_Stick_Input)) + (POV_left * (input_vel.x/Max_Stick_Input));
	
	Input_Target_Vel *= standard_speed;
	Input_Target_Vel.z = 0;

	//Force Z movement to be independent
	float zvel = velocity.z;
	New_vel.z = 0;
	

	//friction coefficent
	float friction = Game_Model::get().get_World()->get_friction_coeff(center);
	//float friction = 0.2;
	//0 to 1, will be determined by tile type eventually
	//(0 represents frictionless environment), (1 immovable environment)
	
	//	New_vel = (New_vel + Vector3f(Input_Target_Vel.x, Input_Target_Vel.y,0));
	
	//New_vel = Input_Target_Vel;
	//New_vel = (1 - friction) * New_vel;


	//Vector3f input_dir = Input_Target_Vel;
	//input_dir.normalize();
	//if(Input_Target_Vel.magnitude() > 0.01)
	//	New_vel += input_dir * Stick_Accel * friction * Game_Model::get().get_time_step();

	//
	////input_dir.normalize();
	////if(Input_Target_Vel.magnitude() < 0.05)	{
	////	input_dir = Vector3f(0,0,0);
	////}
	////if(input_dir.magnitude() > 0.1)
	////	New_vel += input_dir * Stick_Accel * friction * Game_Model::get().get_time_step();
	//
	////Update Variables
	////velocity = New_vel;
	//velocity = New_vel;
	//velocity.z = zvel;

	Vector3f dir(Input_Target_Vel - New_vel);		//Determine vector difference of current v, and player desired v
	Vector3f Input_Accel_Dir(dir.normalize());	//The acceleration vector, based on above
	
	if(Input_Target_Vel.magnitude() < 0.05)	{
		Input_Accel_Dir = Vector3f();		//If Player isn't pushing on stick, don't change velocity at all.
		if(friction == Ice_friction) 
			New_vel *= (1 - friction/5);			//And do a more powerful effect of friction
		else
			New_vel *= (1 - friction);	
	}
											
	//How much the player can control the new direction is also effected by friction
	Input_Accel_Dir *= Stick_Accel * friction;
	New_vel *= (1 - friction/15);
	New_vel += Input_Accel_Dir * Game_Model::get().get_time_step();

	//
	////If the speed is close to player desired, then just set it to player desired speed
	//if(abs(New_vel.magnitude() - Input_Vel_Max.magnitude()) < 1)
	//	New_vel = Input_Vel_Max;

	velocity = New_vel;
	velocity.z = zvel;

	//Animations
	if (velocity.x <= 0.5 && velocity.y <= 0.5 && is_on_ground())
		switch_state(STAND);
	else if ((velocity.x >= 0.5 || velocity.y >= 0.5) && is_on_ground())
		switch_state(WALK);
	else {}

	
}


 

void Player::handle_struct_type_change(bool left, bool right)	{
	if(left && right)
		return;
	if(!left && !right)
		return;

	switch(Selection)	{
	case SNOWMAN:
		Selection = FORT;
		if(left) Selection = HEALING_POOL;
		break;
	case FORT:
		Selection = SNOW_FACTORY;
		if(left) Selection = SNOWMAN;
		break;
	case SNOW_FACTORY:
		Selection = HEALING_POOL;
		if(left) Selection = FORT;
		break;
	case HEALING_POOL:
		Selection = SNOWMAN;
		if(left) Selection = SNOW_FACTORY;
		break;
	default:
		Selection = FORT;
		break;
	}


}



void Player::determine_active_view(bool build, bool mini)	{
	mini_open = mini;
	//build_open = build && !mini;
	build_open = false;
}

Structure_Type Player::select_type(const Vector2f &stick)	{
	if(stick.magnitude() == 0	||
		(stick.x < 0.1 && stick.x > -0.1 && stick.y < 0.1 && stick.y > -0.1))
		return NOTHING;

	float mytheta = atan2(stick.y, stick.x);
	if(mytheta < 0)
		mytheta += 2*Global::pi;

	stick_theta = mytheta;
		//changes the stick input into an angle ,
	//the we define the type by region of angle

	//Joystick points right
	if(	stick_theta > Global::three_pi_over_two + Global::pi/4 ||
			stick_theta < Global::pi/4)
			return SNOWMAN;
	//Up
	if(stick_theta < Global::pi - Global::pi/4 &&
		stick_theta > Global::pi/4)
		return FORT;

	//Left
	if(stick_theta < Global::pi + Global::pi/4 &&
		stick_theta > Global::pi_over_two + Global::pi/4)
		return SNOW_FACTORY;

	//Down
	if(stick_theta < Global::three_pi_over_two + Global::pi/4 && 
		stick_theta > Global::three_pi_over_two - Global::pi/4)
		return HEALING_POOL;
}








bool Player::vibrate_feedback()	{

	if(ShakeTime.seconds() > 0.4)	{
		ShakeTime.stop();
		ShakeTime.reset();
	}
	if(ShakeTime.seconds() > 0)
		return true;

	return false;
}







void Player::add_message(const Zeni::String &msg, int priority, float seconds)
{
	if (message.is_over() || priority >= message.priority)
	{
		message = Message(msg, priority, seconds);
	}
}

bool Player::has_message() const
{
	return !message.is_over();
}

Zeni::String Player::get_message() const
{
	return message.msg;
}

void Player::next_tip()
{	
	stats.tips++;
	if (!tips.size())
	{
		add_message("No Tips Available");
		return;
	}
	
	add_message(tips[cur_tip++%tips.size()], 10000, 10);
}

void Player::reset_tips()
{
	tips.clear();
	cur_tip = 0;
}

