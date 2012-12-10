#include "Base.h"
#include "Team.h"
#include "Player.h"
#include "Game_Model.h"

using namespace std;
using namespace Zeni;


Base::Base(Team *team, Tile* tile_,
				const Zeni::Point3f &base_) :
	Healing_Pool(team, tile_, base_)
{
	switch(owner->get_Team_Index())	{
	case BLUE:
		rotation += Quaternion(3.1415179*(1/6),0,0);
		break;
	case GREEN:
		rotation += Quaternion(3.1415179*(5/6),0,0);
		break;
	case RED:
		rotation += Quaternion(3.1415179*(7/12),0,0);
		break;
	case ORANGE:
		rotation += Quaternion(3.1415179*(1/3),0,0);
		break;
	default:
		break;
	}
	create_body();
}


Base::~Base(void)
{
}

void Base::update(const float &time)
{
	size = Vector3f(100,100,100);
	Structure::update(time);
	Status = BUILT;
}

const model_key_t Base::get_model_name() const 
{
	string Teamname;
	switch(owner->get_Team_Index())	{
	case BLUE:
		return "bluebase";
	case GREEN:
		return "greenbase";
	case RED:
		return "redbase";
	case ORANGE:
		return "orangebase";
	default:
		return "bluebase";
	}
}

void Base::create_body()		{
	Point3f Top = Seen_Object::get_top_center();
	Top.z - 10;
	Point3f Bot = Seen_Object::get_bottom_center();
	body = Zeni::Collision::Capsule(Top, Bot, size.z/2);
}