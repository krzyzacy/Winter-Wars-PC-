#pragma once
#include "Structure.h"

class Tree : public Structure
{
public:
	Tree(Team *team, Tile* tile_,
				const Zeni::Point3f &base_);
	~Tree(void);

	void update(const float&);

	void destabilize_network();

	const model_key_t get_model_name() const;

private:
	Animator *get_animator() const;
	Zeni::Sound_Source * nyan;

};