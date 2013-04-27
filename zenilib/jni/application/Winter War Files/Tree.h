#pragma once
#include "Structure.h"

class Tree : public Structure
{
public:
	Tree(Team *team, Tile* tile_,
				const Zeni::Point3f &base_);
	~Tree(void);

	void update(const float&);
	
	virtual Structure_Type get_type()
	{ return TREE;}

	void destabilize_network();

	void handle_player_collision(Player *P);

	const model_key_t get_model_name() const;

private:
	void create_body();

	Animator *get_animator() const;
	Zeni::Sound_Source * nyan;

};