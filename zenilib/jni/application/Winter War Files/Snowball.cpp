#include "Snowball.h"
#include "Game_Model.h"
#include "Player.h"

#include <zenilib.h>

const int Snowball::snowball_ID_c = 2;

const float Launch_Speed = 700;

using namespace Zeni;

Snowball::Snowball(Player *p, const Zeni::Point3f &center_,
              const Zeni::Vector3f &size_) :
	Moveable(center_, size_)	
	, damage_dealt(false), damage(size_.magnitude() * 1.2)
	, owner(p), team(p->get_team())
{
	Lifespan.start();
}

Snowball::Snowball(Team *t, const Zeni::Point3f &center_,
              const Zeni::Vector3f &size_) :
	Moveable(center_, size_)	
	, damage_dealt(false), damage(size_.magnitude() * 1.2)
	, owner(0), team(t)
{
	Lifespan.start();
}

Snowball::~Snowball(void)
{
}

int Snowball::get_Team_Index()	{
	return owner->get_Team_Index();
}


void Snowball::update(const float &time)
{
	Moveable::update(time);

	if(damage_dealt)
		size *= 0.95;

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
	deal_damage();
}

void Snowball::on_ground()
{
//	damage_dealt = true;
//	alive = false;
//	set_velocity(Vector3f());
}

void Snowball::get_thrown(const Vector3f &dir, const float &spd)
{
	//accelerate(dir*force);
	Moveable::set_velocity(dir*spd);
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
