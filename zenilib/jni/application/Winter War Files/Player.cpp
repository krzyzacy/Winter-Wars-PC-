#include "Player.h"

#include "Game_Model.h"
#include "Snowball.h"
#include "Team.h"
#include "World.h"
#include "Object_factory.h"

#include <zenilib.h>

using namespace std;
using namespace Zeni;

const int Player::player_ID_c = 1;
const float standard_speed = 150;
const float turn_speed = 2;

const float Max_Snow_Amount = 100;
extern const float Max_Player_Health = 100;
const float packing_rate = 20;
const float snow_depletion_rate = 20;
const float snow_absorbtion_rate = 50;

const int Max_Stick_Input	= 32768;
const float Building_Recharge_Time = 1;


const Vector3f jump_vec(0,0,500);
const float  Stick_Accel = 200;


Player::Player(const Zeni::Point3f &center_) 
	: Moveable(center_ , Vector3f(20.0f,20.0f,20.0f)), m_camera(center_, Quaternion(), 5.0f, 2000.0f),
	current_radius(0.0f), Snow_in_Pack(Max_Snow_Amount), health(Max_Player_Health), 
	myTeam(0), Jumping(ON_GROUND), Builder(REST), mini_open(false), build_open(false), Selection(NOTHING),
	stick_theta(0.0f)
{
	//field of view in y
	m_camera.fov_rad = Zeni::Global::pi / 3.0f;
	//rotation = m_camera.orientation + Quaternion(Global::pi_over_two, 0, 0);
}


Player::~Player(void)
{
}

void Player::adjust_pitch(float phi) {
    const Quaternion backup = m_camera.orientation;
    const Vector3f backup_up = m_camera.get_up();

    m_camera.adjust_pitch(phi);

    if(m_camera.get_up().k < 0.0f && backup_up.k >= 0.0f)
      m_camera.orientation = backup;
}

void Player::turn_left(float theta) {
		m_camera.turn_left_xy(theta*turn_speed);
		//Quaternion LR_Only = m_camera.orientation;
		//Here take out pitch and roll	
		//LR_Only *= Quaternion(1,0,0); Doesn't work, think we need math
		//rotation = LR_Only + Quaternion (Global::pi_over_two, 0, 0);
		//Pre render?
		rotation = m_camera.orientation + Quaternion(Global::pi_over_two, 0,0);
}

void Player::update(const float &time)	{
	backup = center;
	
	Moveable::update(time);

	m_camera.position = center;
	
}

void Player::off_map()
{
	center.x = backup.x;
	center.y = backup.y;
}

void Player::hit_tile()
{
	center.x = backup.x;
	center.y = backup.y;
}

void Player::on_ground()
{
	if(velocity.z < 0)
		velocity.z = 0;
}

void Player::get_damaged(float damage)
{
	health -= damage;
	//Add respawn stuff / checks here / and the suprise
	ShakeTime.start();
}

void Player::throw_ball()		{
	if(current_radius > 0)	{
		Snowball *sb = new Snowball(this, center+m_camera.get_forward(), 
										Vector3f(current_radius, current_radius,current_radius));
		sb->get_thrown(m_camera.get_forward());
		current_radius = 0;
		Game_Model::get().add_moveable(sb);
	}
	//if radius is 0, means out of snow, and therefore don't throw
}

void Player::charge_ball()	{
	//This represents when the player is "packing" snow into a ball
	const float time = Game_Model::get().get_time_step();
		if(Snow_in_Pack <= 0)		
			Snow_in_Pack = 0;
		else	{
			current_radius += packing_rate * time;
			Snow_in_Pack -= snow_depletion_rate * time;
		}
}

void Player::pack_snow()	{
	//This will change, but exists for now as a simple test function
	const float time = Game_Model::get().get_time_step();
	if(Snow_in_Pack >= Max_Snow_Amount)
		Snow_in_Pack = Max_Snow_Amount;
	else
		Snow_in_Pack += snow_absorbtion_rate * time;
}

 void Player::calculate_movement(const Vector2f &input_vel)	{
	//Here is where the magic happens for player
	//input_vel represents joystick desire of where player wants to go
	if(mini_open)	{
		velocity = Vector3f(0,0, velocity.z);
		return;
	}

	Vector3f POV_face = m_camera.get_forward().get_ij().normalize();
	Vector3f POV_left = m_camera.get_left().get_ij().normalize();

	float zvel = velocity.z;
	Vector3f New_vel(velocity);
	Vector3f Input_Vel_Max = (standard_speed * POV_face * input_vel.y/Max_Stick_Input) +
													(standard_speed * POV_left * input_vel.x/Max_Stick_Input);
	//Now the clever shit
	Vector2f dir = input_vel;
	dir.normalize();
	Vector3f Input_Accel_Dir(dir.x, dir.y, 0);
	//&&& ICE AND FRICTION FACTOR HERE, WILL NEED GET TILE
	const float friction = 1;	//0 to 1, will be an input laters
	float grip = Stick_Accel * friction;
	Input_Accel_Dir *= grip;
	New_vel += Input_Accel_Dir * Game_Model::get().get_time_step();

	//HOW TO IMPLEMENT INPUT_VEL_MAX AS LIMIT??
	float diff = abs(New_vel.magnitude() - Input_Vel_Max.magnitude());
	if(diff <= 100 || diff > 5000 || Input_Vel_Max.magnitude() == 0)
		New_vel = Input_Vel_Max;

	velocity = New_vel;
	velocity.z = zvel;

	//OLD WAY
	//Adding Ice effects later, for now straight up movement
	//float zvel = velocity.z;
	//velocity = (POV_face * input_vel.y) + (POV_left * input_vel.x);
	//velocity *= standard_speed;
	//velocity.z = zvel;
	
}
 
void Player::jump()	{
	switch(Jumping)	{
	case ON_GROUND:
		AirTime.start();
		accelerate(jump_vec, Game_Model::get().get_time_step());
		Jumping = BOOST;
		break;
	case BOOST:
		if(AirTime.seconds() <= 0.4)	
			accelerate(jump_vec, Game_Model::get().get_time_step());
		else	{
			Jumping = FALLING_WITH_STYLE;
			AirTime.stop();
			AirTime.reset();
		}
		break;
	case FALLING_WITH_STYLE:
		if(is_on_ground())
			Jumping = ON_GROUND;
		break;
	case JET_PACK:
		accelerate(jump_vec, Game_Model::get().get_time_step());
		break;
	default:
		if(is_on_ground())
			Jumping = ON_GROUND;
		else
			Jumping = FALLING_WITH_STYLE;
		break;
	}
	
}

void Player::handle_build_menu(const Vector2f &norml_stick)	{
	select_type(norml_stick);
	switch(Builder)	{
	case REST:
		if(build_open)	
			Builder = SELECT_BUILDING;
			//Now bring up the build selection map
		break;
	case SELECT_BUILDING:
		if(!build_open)	{
			Selection = select_type(norml_stick);
			if(Selection == NOTHING)
				Builder = REST;
			else
				Builder = CREATE_BUILDING;
		}
		break;
	case CREATE_BUILDING:
		if(create_building(Selection))	{
			Builder = RECHARGE_BUILD;
			BuildTime.start();
		}
		else
			Builder = REST;

		Selection = NOTHING;
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

void Player::determine_active_view(bool build, bool mini)	{
	mini_open = mini;
	build_open = build && !mini;
}

Structure_Type Player::select_type(const Vector2f &stick)	{
	if(stick.magnitude() == 0	||
		(stick.x < 0.1 && stick.x > -0.1 && stick.y < 0.1 && stick.y > -0.1))
		return NOTHING;

	float mytheta = atan2(stick.y, stick.x);
	if(mytheta < 0)
		mytheta += 2 * Global::pi;

	stick_theta = mytheta;
		//changes the stick input into an angle ,
	//the we define the type by region of angle

	//Joystick points left
	if(	stick_theta > Global::three_pi_over_two + Global::pi/4 ||
			stick_theta < Global::pi/4)
			return SNOWMAN;
	//Down
	if(stick_theta < Global::pi - Global::pi/4 &&
		stick_theta > Global::pi/4)
		return FORT;

	//Right
	if(stick_theta < Global::pi + Global::pi/4 &&
		stick_theta > Global::pi_over_two + Global::pi/4)
		return SNOW_FACTORY;

	//Up
	if(stick_theta < Global::three_pi_over_two + Global::pi/4 && 
		stick_theta > Global::three_pi_over_two - Global::pi/4)
		return HEALING_POOL;
}

bool Player::create_building(Structure_Type Building)	{
	//Returns true if building was created, false if unable
		
	Tile *t = Game_Model::get().get_World()->player_is_looking_at(center, m_camera.get_forward());
	//Checks if the tile can be built upon
	if(!myTeam->tile_is_ready(t, Building))
		return false;

	Game_Model::get().add_structure(create_structure(Building, t, myTeam));
	return true;
}

void Player::jet_pack_mode(bool state)	{
	if(state) //Super easy to add as a power up
		Jumping = JET_PACK;
	else if(Jumping == JET_PACK)
		Jumping = FALLING_WITH_STYLE;
}

void Player::raise_tile()	{
	//Add restrictions and shit to this later
	//wnership etc.
	Game_Model::get().get_World()->raise_tile(center);
}

void Player::lower_tile()	{
	Game_Model::get().get_World()->lower_tile(center);
}

void Player::create_body()
{
	body = Zeni::Collision::Capsule(center + Vector3f(0, 0 , size.z*0.25)
		, center - Vector3f(0, 0, size.z*0.25), size.z*0.25);
}

int Player::get_Team_Blocks() const	{
	return myTeam->get_Resources();
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