#include "Snowball.h"
#include "Game_Model.h"

#include <zenilib.h>

const int Snowball::snowball_ID_c = 2;

const float Launch_Speed = 700;

using namespace Zeni;

Snowball::Snowball(const Player *p, const Zeni::Point3f &center_,
              const Zeni::Vector3f &size_) :
	Moveable(center_, size_)	
	, damage_dealt(false), damage(size_.magnitude() * 1.2)
	, owner(p)
{
	Lifespan.start();
}


Snowball::~Snowball(void)
{
}

void Snowball::update(const float &time)
{
	Moveable::update(time);

	if(damage_dealt)
		size *= 0.99;

	//Temporary, so we don't have infinite snowballs flying around chewing up resources
	if(Lifespan.seconds() > 15 || Melting.seconds() > 3)	{		
		mark_for_deletion();
	}
}

void Snowball::off_map()
{
	mark_for_deletion();
}

void Snowball::hit_tile()
{
//	alive = false;
}

void Snowball::on_ground()
{
//	damage_dealt = true;
//	alive = false;
//	set_velocity(Vector3f());
}

void Snowball::get_thrown(const Vector3f &dir)
{
	//accelerate(dir*force);
	Moveable::set_velocity(dir*Launch_Speed);
}

float Snowball::deal_damage()	{
	if(!damage_dealt)	{
		damage_dealt = true;
		Lifespan.stop();
		Melting.start();
		Moveable::set_velocity(Vector3f());
		perform_contact_effects();
		return damage;
	}
	return 0;
}

void Snowball::perform_contact_effects()	{
	//Add cool shit to the game model here, possibly sound effects
}

void Snowball::create_body()
{
	body = Zeni::Collision::Sphere(center, size.z);
}
