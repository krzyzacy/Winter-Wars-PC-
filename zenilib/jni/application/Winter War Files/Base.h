#pragma once
#include "Healing_Pool.h"

class Base : public Healing_Pool
{
public:
	Base(Team *team, Tile* tile_,
				const Zeni::Point3f &base_);
	~Base(void);

	void update(const float&);

	
	virtual Structure_Type get_type()
	{ return BASE;}

	const model_key_t get_model_name() const;

	void receive_hit(float damage);

	void handle_player_collision(Player *P);

private:
	
	void create_body();

};