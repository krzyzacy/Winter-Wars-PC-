#pragma once
#include "Structure.h"

class Team;

class Snowman : public Structure
{
public:
	Snowman(Team *team, Tile* tile_,
				const Zeni::Point3f &base_);
	~Snowman(void);

	void update(const float&);
	
	virtual Structure_Type get_type()
	{ return SNOWMAN;}

	const model_key_t get_model_name() const;

	void handle_player_in_range(Team *t, Zeni::Collision::Capsule &person);

	virtual int get_intake();

private:
	Zeni::Point3f left_launch;
	Zeni::Point3f right_launch;

	bool left;
	Zeni::Chronometer<Zeni::Time> reload_time;
	Zeni::Chronometer<Zeni::Time> targeting_delay;


	std::list<Zeni::Point3f> targets;
	
	void create_body();
	Zeni::Collision::Capsule field;

	// Animation
	Animator *get_animator() const;
};

