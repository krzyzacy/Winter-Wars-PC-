#pragma once
#include "Healing_Pool.h"

class Base : public Healing_Pool
{
public:
	Base(Team *team, Tile* tile_,
				const Zeni::Point3f &base_);
	~Base(void);

	void update(const float&);

	const model_key_t get_model_name() const;

private:
	
	void create_body();

};