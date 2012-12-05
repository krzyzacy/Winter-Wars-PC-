#pragma once
#include "Structure.h"

class Snowman : public Structure
{
public:
	Snowman(Team *team, Tile* tile_,
				const Zeni::Point3f &base_);
	~Snowman(void);

	void update(const float&);

	const model_key_t get_model_name() const;

private:
	
	void create_body();
};

