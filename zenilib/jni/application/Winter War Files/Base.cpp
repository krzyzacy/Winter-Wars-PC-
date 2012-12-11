#include "Base.h"
#include "Team.h"
#include "Player.h"
#include "Game_Model.h"

using namespace std;
using namespace Zeni;

const float PI = 3.141517;

Base::Base(Team *team, Tile* tile_,
				const Zeni::Point3f &base_) :
	Healing_Pool(team, tile_, base_)
{
	create_body();
	center.z += 230;
}


Base::~Base(void)
{
}

void Base::update(const float &time)
{
	Status = BUILT;
	switch(owner->get_Team_Index())	{
		case BLUE:
			rotation = Quaternion(0,0,0);
			break;
		case GREEN:
			rotation = Quaternion(2.0*PI*(1.0/3.0),0,0);
			break;
		case RED:
			rotation = Quaternion(2.0*PI*(-1.0/6.0),0,0);
			break;
		case ORANGE:
			rotation = Quaternion(2.0*PI*(2.0/3.0),0,0);
			break;
		default:
			rotation += Quaternion(2.0,0,0);
			break;
	}

	size = Vector3f(642,642,650);

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

void Base::handle_player_collision(Player *P)	{

	if (Connected_to_Team)
		{
		if (P->get_team() == owner)	
			{
			P->healing_waters(Healing_rate * Game_Model::get().get_time_step());
			}
		}
}

void Base::receive_hit(float damage)	{
//Do nothing, base will not take damage
}