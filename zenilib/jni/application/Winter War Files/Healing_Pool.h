#pragma once
#include "Structure.h"

class Healing_Pool : public Structure
{
public:
	Healing_Pool(Team *team, Tile* tile_,
				const Zeni::Point3f &base_);
	~Healing_Pool(void);

	void update(const float&);

	const model_key_t get_model_name() const;

private:

	void create_body();
};