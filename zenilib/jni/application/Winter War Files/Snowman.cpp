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
	center.z -= 8;
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
	Structure::update(time);
	//Magic happens here, need to decide how this will works, def statemachine

	if(reload_time.seconds() > 0.05)	{
		Point3f aim = targets.front();
		targets.pop_front();
		Point3f Origin = right_launch;
		if(left) Origin = left_launch;
		Snowball* sb = new Snowball(0, Origin, Snow_size);
		sb->get_thrown(Origin - aim);
		Game_Model::get().add_moveable(sb);
		left = !left;
		reload_time.reset();
	}

	
}

const model_key_t Snowman::get_model_name() const 
{
	switch(owner->get_Team_Index())	{
	case BLUE:
		return ("blue_snowman");
	case GREEN:
		return ("green_snowman");
	case RED:
		return ("red_snowman");
	case ORANGE:
		return ("orange_snowman");
	default:
		return ("blue_snowman");
		break;
	}
}

void Snowman::handle_player_in_range(Team *t, Collision::Capsule &person)	{
	//Could add velocity stuff later, to predict motion, but fuck it for
	//if(t->get_Team_Index() == hex->get_team())
	//	return;

	if(!person.intersects(field))
		return;
	
	//Target the player if targeting threshold has passed
	if(targeting_delay.seconds() > 0.05)	{
		targets.push_back(person.get_end_point_a());
		targeting_delay.reset();
	}
}

void Snowman::create_body()		{
	Point3f Top = Seen_Object::get_top_center();
	Point3f Bot = Seen_Object::get_bottom_center();
	body = Zeni::Collision::Capsule(Top, Bot, size.z/4);

	field = Zeni::Collision::Capsule(Top += Vector3f(0,0, 20), Bot, 200);

}