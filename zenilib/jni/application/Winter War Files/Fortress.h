#pragma once
#include "Structure.h"

class Fortress : public Structure
{
public:
	Fortress(Team *team, Tile* tile_,
				const Zeni::Point3f &base_);
	~Fortress(void);

	void update(const float&);

	const model_key_t get_model_name() const;

private:
	// Stuff?

};