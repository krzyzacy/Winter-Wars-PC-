#include "Player.h"

#include "Game_Model.h"
#include "Snowball.h"

#include <zenilib.h>

using namespace std;
using namespace Zeni;

const int Player::player_ID_c = 1;

const float standard_speed = 100;

Player::Player(const Zeni::Point3f &center_) 
	: Moveable(center_), m_camera(center_)
{
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

	m_camera.position += velocity * time;
}


void Player::throw_ball()
{
	Snowball *sb = new Snowball(center+m_camera.get_forward());

	sb->get_thrown(m_camera.get_forward(), 100);

	Game_Model::get().add_moveable(sb);
}

void Player::calculate_movement(const Vector2f &input_vel)	{
	//Here is where the magic happens for player
	//input_vel represents joystick desire of where player wants to go
	Vector3f POV_face = m_camera.get_forward().get_ij().normalize();
	Vector3f POV_left = m_camera.get_left().get_ij().normalize();

	//Adding Ice effects later, for now straight up movement

	velocity = (POV_face * input_vel.y * standard_speed) + (POV_left * input_vel.x * standard_speed);
	
}


