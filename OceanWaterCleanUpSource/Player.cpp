#include "Player.h"

#include "Utility.h"
#include "Game_Model.h"
#include "Snowball.h"

#include <zenilib.h>

using namespace Zeni;

const int Player::player_ID_c = 2;
int Player::num_players = 0;
const Vector3f player_size = Vector3f(20,20,20);
	
const float default_snow_size = 10.0f;
const float default_snow_rate = 95.0f;
const float max_packed_c = 200.0f;

Player::Player(const Zeni::Point2f &pos_) 
:  Game_Object(Vector3f(pos_.x
					, pos_.y
					, player_size.k/2) 
				, player_size, 1000000)
	, score(0)
	, num(++num_players)
	, being_packed(default_snow_size)
	, m_camera(get_pos() + player_size.get_k(),
				Quaternion(), 1.0f, 10000.0f)
{
	update_camera_pos();
}

Player::~Player(void)
{
	num_players--;
}

void Player::render() const
{

}

void Player::update()
{	
    /** Get forward and left vectors in the XY-plane **/
    const Vector3f forward = m_camera.get_forward().get_ij().normalized();
    const Vector3f left = m_camera.get_left().get_ij().normalized();

	 /** Get velocity vector split into a number of axes **/
 //   accelerate((m_controls.forward - m_controls.back) * forward
  //              + (m_controls.left - m_controls.right) * left);
	
		 /** Get velocity vector split into a number of axes **/
    m_velo = (m_controls.forward - m_controls.back) * Game_Model::get().time_step() * 75.0f *  forward
                            + (m_controls.left - m_controls.right) * Game_Model::get().time_step() * 75.0f * left;
	
	int world_size = 1250;


	Game_Object::update();

	if (get_pos().x  > world_size || get_pos().x < -1*world_size)
		move_back();
	
	if (get_pos().y > 1*world_size || get_pos().y < -1*world_size)
		move_back();

	old_pos = get_pos();
	update_camera_pos();
}


void Player::update_camera_pos()
{
	m_camera.position = get_pos() + player_size.get_k();
}


void Player::throw_ball()
{
	m_controls.throw_ball = false;

	if (snowballs.empty())
	{
		return;
	}

	(*snowballs.rbegin())->get_thrown(get_pos(), m_camera.get_forward());
	Game_Model::get().add_obj(*snowballs.rbegin());
	snowballs.pop_back();
	play_sound("throw");
}

void Player::pack_ball()
{
	if (being_packed < max_packed_c)	
	{
		being_packed += default_snow_rate * Game_Model::get().time_step();
	
	}
	m_controls.packed = true;
}

void Player::finish_packing()
{	
	if (m_controls.packed)
	{
		m_controls.packed = false;
		snowballs.push_front(new Snowball(being_packed, this));
		being_packed = default_snow_size;
		throw_ball();
	}
}

void render_charge(float charge)
{
	Vertex2f_Color p0(Point2f(0.0f, 0.0f), Color(.25,1,0,0));
    Vertex2f_Color p1(Point2f(0.0f, 25.0f),  Color(.25,1,0,0));
    Vertex2f_Color p2(Point2f(200.0f, 25.0f),  Color(.25,1,0,0));
    Vertex2f_Color p3(Point2f(200.0f, 0.0f), Color(.25,1,0,0));

	Quadrilateral<Vertex2f_Color> q(p0, p1, p2, p3);

	get_Video().render(q);

	float length = (charge - default_snow_size)/(max_packed_c - default_snow_size)*200.0f;

	Vertex2f_Color p20(Point2f(0.0f, 0.0f), Color(1,0,0,0));
    Vertex2f_Color p21(Point2f(0.0f, 25.0f),  Color(1,0,0,0));
    Vertex2f_Color p22(Point2f(length, 25.0f),  Color(1,0,1,0));
    Vertex2f_Color p23(Point2f(length, 0.0f), Color(1,0,1,0));

	Quadrilateral<Vertex2f_Color> q2(p20, p21, p22, p23);

	get_Video().render(q2);

}

void render_time(int time_left, int y)
{	
	Color col ;

	if (time_left > 30)
		col = Color(1.0,0.0,1.0,0);
	else if (time_left > 10)
	{
		col = Color(1.0,1.0,1.0,0);
	}	
	else
	{		
		col = Color(1.0,1.0,0,0);
		get_Fonts()["title"].render_text(
		itoa(time_left)
			, Point2f(screen_x_c/2, 200), col, ZENI_CENTER);
	
	}
	get_Fonts()["medium"].render_text(
		"Time:"
			, Point2f(screen_x_c - 100, y), col);

	get_Fonts()["medium"].render_text(
		itoa(time_left)
			, Point2f(screen_x_c - 90, y+50), col);
	

}

void Player::render_hud() const
{
	get_Fonts()["medium"].render_text(
		"Score: "+ itoa(score)
		, Point2f(screen_x_c / 2, screen_y_c - 100), Color(1.0,1.0,1.0,0));

	render_time(Game_Model::get().get_time_left(), 0);
	render_charge(being_packed);

}

void Player::adjust_pitch(const float &phi) {
    const Quaternion backup = m_camera.orientation;
    const Vector3f backup_up = m_camera.get_up();

    m_camera.adjust_pitch(phi);

    if(m_camera.get_up().k < 0.0f && backup_up.k >= 0.0f)
      m_camera.orientation = backup;
}

void Player::turn_left_xy(const float &theta) {
	m_camera.turn_left_xy(theta);
}
