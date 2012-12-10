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
	create_body();
}


Base::~Base(void)
{
}

void Base::update(const float &time)
{
	Structure::update(time);
	Status = BUILT;
}

const model_key_t Healing_Pool::get_model_name() const 
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