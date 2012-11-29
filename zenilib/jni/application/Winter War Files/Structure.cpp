#include "Structure.h"

#include <zenilib.h>

using namespace Zeni;

const int Structure::structure_ID_c = 3;

Structure::Structure(Team *team,
			const Zeni::Point3f &position_,
			float radius
			) :
	Seen_Object(position_, Vector3f(1,1,1)*radius), 
	owner(team)
{
}


Structure::~Structure(void)
{
}

void Structure::update(const float &time)
{

}

void Structure::create_body()
{

}