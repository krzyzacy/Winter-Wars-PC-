#include "Snowman.h"
#include "Team.h"
#include "Player.h"
#include "Tile.h"
#include "Snowball.h"
#include "Game_Model.h"

using namespace std;
using namespace Zeni;

const Vector3f Snow_size(8,8,8);

Snowman::Snowman(Team *team, Tile* tile_,
				const Zeni::Point3f &base_) :
	Structure(team, tile_, base_), left(true)
{
	animation_state = new Present_wrapped();
	create_body();
	Health = Struct_Integrity[SNOWMAN];
	left_launch = center - Vector3f(50, 0,0);
	right_launch = center + Vector3f(50, 0,0);
	targeting_delay.start();
	reload_time.start();
}


Snowman::~Snowman(void)
{
}

void Snowman::update(const float &time)
{
	float turn = 0;
	Vector3f axis(0,10,0);
	Structure::update(time);

	//Magic happens here, need to decide how this will works, def statemachine
	if (Status == UNWRAP_MODE)
		{
		center.z -= 8;
		Status = BUILT;
		}

	if (Status != PRESENT_MODE && Status != UNWRAP_MODE)
		{
		if (Connected_to_Team)
			{
			if(targets.empty())
				switch_state(SM_STAND);

			if(!targets.empty() && reload_time.seconds() > 0.5)	{
				Point3f aim = targets.front();
				targets.pop_front();
				turn = axis.angle_between((center - aim).get_ij());
				if (center.x > aim.x) turn *= -1;
				rotation = Quaternion(turn,0,0);
				//Launch depending on the orientation of the snowman
				left_launch = center - Vector3f(50*cos(turn), 50*sin(turn),0);
				right_launch = center + Vector3f(50*cos(turn), 50*sin(turn),0);
				Point3f Origin = right_launch;
				if(left) Origin = left_launch;
				Game_Model::get().play_snowballthrow();
				Snowball* sb = new Snowball(owner, Origin, Snow_size);
				Vector3f sight_line(aim - Origin);
				//sight_line.z += 20;
				//sb->get_thrown(aim - Origin);
				sb->get_thrown(sight_line.normalize(), 600);
				Game_Model::get().add_moveable(sb);
				if(left)
					switch_state(SM_THROWR);
				else
					switch_state(SM_THROWL);
				left = !left;
				reload_time.reset();
				}
			}
		else
			switch_state(SM_ISO);
		}
}

const model_key_t Snowman::get_model_name() const 
{
	string Teamname;
	switch(owner->get_Team_Index())	{
	case BLUE:
		Teamname = "blue";
		break;
	case GREEN:
		Teamname = "green";
		break;
	case RED:
		Teamname = "red";
		break;
	case ORANGE:
		Teamname = "orange";
		break;
	default:
		Teamname = "blue";
		break;
	}
	return Teamname + animation_state->get_model_name();
}

void Snowman::handle_player_in_range(Team *t, Collision::Capsule &person)	{
	//Could add velocity stuff later, to predict motion, but fuck it for
	if(t->get_Team_Index() == hex->get_team())
		return;

	if(!person.intersects(field))
		return;
	
	//Target the player if targeting threshold has passed
	if(targeting_delay.seconds() > 0.5)	{
		Point3f head = person.get_end_point_a() + Vector3f(0,0,20);
		targets.push_back(head);
		targeting_delay.reset();
	}
}

void Snowman::create_body()		{
	Point3f Top = Seen_Object::get_top_center();
	Point3f Bot = Seen_Object::get_bottom_center();
	body = Zeni::Collision::Capsule(Top, Bot, size.z/4);

	field = Zeni::Collision::Capsule(Top + Vector3f(0,0, 20), Bot, 500);

}

Animator *Snowman::get_animator() const
{
	return animation_state;
}

