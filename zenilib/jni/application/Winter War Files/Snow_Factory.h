#pragma once
#include "Structure.h"

class Snow_Factory : public Structure
{
public:
	Snow_Factory(Team *team, Tile* tile_,
				const Zeni::Point3f &base_);
	~Snow_Factory(void);

	void update(const float&);

	const model_key_t get_model_name() const;

	Animator* get_animator();

private:

	Animator *get_animator() const;
	
	void create_body();
};