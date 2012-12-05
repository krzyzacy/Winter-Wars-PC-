#include "Snow_Factory.h"
#include "Team.h"
#include "Tile.h"
#include "Game_Model.h"
#include "World.h"

using namespace std;
using namespace Zeni;

Snow_Factory::Snow_Factory(Team *team, Tile* tile_,
				const Zeni::Point3f &base_) :
	Structure(team, tile_, base_)
{
	create_body();
	list<Tile*> family = Game_Model::get().get_World()->Get_Family(hex);
	for(list<Tile*>::iterator it = family.begin(); it != family.end(); ++it)	{
		(*it)->set_covering(SOFT_SNOW);
	}
	hex->set_covering(SOFT_SNOW);
	Health = Struct_Integrity[SNOW_FACTORY];
}


Snow_Factory::~Snow_Factory(void)
{
	list<Tile*> family = Game_Model::get().get_World()->Get_Family(hex);
	for(list<Tile*>::iterator it = family.begin(); it != family.end(); ++it)	{
		int randomcov = rand() %2;
		if(randomcov == 0) (*it)->set_covering(ICE);
		if(randomcov == 1) (*it)->set_covering(HARD_SNOW);
	}
	hex->set_covering(ICE);
}

void Snow_Factory::update(const float &time)
{
	Structure::update(time);
}

const model_key_t Snow_Factory::get_model_name() const 
{
		switch(owner->get_Team_Index())	{
	case BLUE:
		return ("blue_snowfactory");
	case GREEN:
		return ("green_snowfactory");
	case RED:
		return ("red_snowfactory");
	case ORANGE:
		return ("orange_snowfactory");
	default:
		return ("blue_snowfactory");
		break;
	}
}


void Snow_Factory::create_body()	{
	Point3f Top = Seen_Object::get_top_center();
	Point3f Bot = Seen_Object::get_bottom_center();
	body = Zeni::Collision::Capsule(Top, Bot, size.z/3);
}


