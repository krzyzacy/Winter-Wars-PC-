#include "Player.h"

#include "Game_Model.h"
#include "Snowball.h"

#include <zenilib.h>

using namespace std;
using namespace Zeni;

const int Player::player_ID_c = 1;

const float standard_speed = 100;
const Vector3f jump_vec(0,0,400);


Player::Player(const Zeni::Point3f &center_) 
	: Moveable(center_), m_camera(center_),
	current_radius(0.0f), Snow_in_Pack(Max_Snow_Amount)
{
	m_camera.fov_rad = Zeni::Global::pi / 3.0f;
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
	m_camera.turn_left_xy(theta);
}

void Player::update(const float &time)	{
	Moveable::update(time);
	m_camera.position = center;
}


void Player::throw_ball()
{
	if(current_radius > 0)	{
		Snowball *sb = new Snowball(center+m_camera.get_forward(), 
																Vector3f(current_radius, current_radius,current_radius));
		sb->get_thrown(m_camera.get_forward(), 100);
		current_radius = 0;
		Game_Model::get().add_moveable(sb);
	}
	//if radius is 0, means out of snow, and therefore don't throw
}

void Player::charge_ball(const float &time)	{
	//This represents when the player is "packing" snow into a ball
		if(Snow_in_Pack <= 0)		
			Snow_in_Pack = 0;
		else	{
			current_radius += charge_rate * time;
			Snow_in_Pack -= charge_rate *time;
		}
}

void Player::pack_snow(const float &time)	{
	//This will change, but exists for now as a simple test function
	if(Snow_in_Pack >= Max_Snow_Amount)
		Snow_in_Pack = Max_Snow_Amount;
	else
		Snow_in_Pack += pack_rate * time;
}

 void Player::calculate_movement(const Vector2f &input_vel)	{
	//Here is where the magic happens for player
	//input_vel represents joystick desire of where player wants to go
	Vector3f POV_face = m_camera.get_forward().get_ij().normalize();
	Vector3f POV_left = m_camera.get_left().get_ij().normalize();

	//Adding Ice effects later, for now straight up movement
	float zvel = velocity.z;
	velocity = (POV_face * input_vel.y) + (POV_left * input_vel.x);
	velocity *= standard_speed;

	//float friction; //&&& This will be an input later, or determined based on input
	//velocity *= friction;
	//&&& And also may use a new velocity as a temporary velocity

	velocity.z = zvel;
}

void Player::jump()	{
	accelerate(jump_vec, Game_Model::get().get_time_step());
}

void Player::create_body()
{
	body = Zeni::Collision::Capsule(center + Vector3f(0, 0 , size.z*0.25), center - Vector3f(0, 0, size.z*0.25), size.z*0.5);
}
