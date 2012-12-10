#pragma once
#include "Structure.h"

class Fortress : public Structure
{
public:
	Fortress(Team *team, Tile* tile_,
				const Zeni::Point3f &base_);
	~Fortress(void);

	void update(const float&);
	
	void handle_player_collision(Player *P);

	const model_key_t get_model_name() const;

private:
	Animator *get_animator() const;

	void create_body();

};