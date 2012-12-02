#include "Structure.h"

#include <zenilib.h>

using namespace Zeni;

const int Structure::structure_ID_c = 3;

Structure::Structure(Team *team, Tile* tile_,
				const Zeni::Point3f &position_,	 float radius) :
	Seen_Object(position_, Vector3f(1,1,1)*radius),
	owner(team), Health(100.0), Status(PRESENT_MODE), 
	Connected_to_Team(true), hex(tile_)
{
	//Magic number shift height attempt
	center.z += radius/2;
}


Structure::~Structure(void)
{
}

void Structure::update(const float &time)
{
	Collidable::update(time);
}

void Structure::create_body()
{

}

void Structure::change_height(const float &delta)	{
	center.z += delta;
}