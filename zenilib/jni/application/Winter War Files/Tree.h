#pragma once
#include "Structure.h"

class Tree : public Structure
{
public:
	Tree(Team *team, Tile* tile_,
				const Zeni::Point3f &base_);
	~Tree(void);

	void update(const float&);

	const model_key_t get_model_name() const;

private:
	// Stuff?

};