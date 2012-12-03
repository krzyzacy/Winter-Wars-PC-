#include "Structure.h"
#include "Snowball.h"
#include "Team.h"
#include "Tile.h"

using namespace Zeni;

const int Structure::structure_ID_c = 3;

Structure::Structure(Team *team, Tile* tile_,
				const Zeni::Point3f &position_,	 float radius) :
	Seen_Object(position_, Vector3f(1,1,1)*radius),
	owner(team), Health(1), Status(PRESENT_MODE), 
	Connected_to_Team(true), hex(tile_)
{
	//Magic number shift height attempt
	center.z += radius/2;
}


Structure::~Structure(void)
{
}

void Structure::receive_hit(Snowball* S)	{
	Health -= S->deal_damage();
	if(Health < 0)
		Status = DESTROYED;
}

void Structure::update(const float &time)
{
	Collidable::update(time);
	if(Status == DESTROYED)	{
		perform_destruction_effects();
		owner->remove_tile(hex);
		hex->destroy_structure();
	}
}

void Structure::perform_destruction_effects()	{


}

void Structure::create_body()
{
	body = Zeni::Collision::Capsule(center + Vector3f(0, 0 , size.z)
		, center - Vector3f(0, 0, size.z), size.z);
}

void Structure::change_height(const float &delta)	{
	center.z += delta;
}