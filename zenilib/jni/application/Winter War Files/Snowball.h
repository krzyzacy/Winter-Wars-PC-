#pragma once

#include "Moveable.h"

#include <zenilib.h>

class Collision_Table;
class Player;
class Team;

extern const float Launch_Speed;


class Snowball :
	public Moveable
{
public:
	Snowball(Player *p, const Zeni::Point3f &center_,
              const Zeni::Vector3f &size_ = Zeni::Vector3f(1,1,1));
	Snowball(Team *t, const Zeni::Point3f &center_,
              const Zeni::Vector3f &size_ = Zeni::Vector3f(1,1,1));


	~Snowball(void);

	bool Snow_man_Generated()	{return (owner == 0);}
	
	void update(const float &time);

	void get_thrown(const Zeni::Vector3f &dir, const float &spd = Launch_Speed);

	float deal_damage();

	void perform_contact_effects();

	int get_Team_Index();

	virtual int get_ID() const 
		{return snowball_ID_c;}

	const model_key_t get_model_name() const
		{return "snowball";}

// Collision Body
	void create_body();

private:
	Player *owner;
	Team *team;

	Zeni::Chronometer<Zeni::Time> Lifespan;
	Zeni::Chronometer<Zeni::Time> Melting;
	bool damage_dealt;
	float damage;
	
	virtual void off_map();
	virtual void hit_tile();
	virtual void on_ground();

	// Collison Stuff
	const static int snowball_ID_c;
	friend Collision_Table;

	Zeni::Collision::Sphere body;
};

