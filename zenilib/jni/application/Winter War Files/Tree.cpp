#include "Tree.h"
#include "Team.h"

#include "Game_Model.h"

Tree::Tree(Team *team, Tile* tile_,
				const Zeni::Point3f &base_) :
	Structure(team, tile_, base_, 200)
{	
	if (!owner)
		animation_state = new Tree_unowned();
	else
		animation_state = new Tree_owned();


	Game_Model::get().tree_claimed(owner);
}


Tree::~Tree(void)
{
}

void Tree::update(const float &time)
{

}

const model_key_t Tree::get_model_name() const 
{
	std::string Teamname;
	if (!owner)
		return animation_state->get_model_name();

switch(owner->get_Team_Index())	{
	case BLUE:
		Teamname = "blue";
		break;
	case GREEN:
		Teamname = "green";
		break;
	case RED:
		Teamname = "red";
		break;
	case ORANGE:
		Teamname = "orange";
		break;
	default:
		Teamname = "blue";
		break;
	}
	return Teamname + animation_state->get_model_name();
}

Animator *Tree::get_animator() const
{
	return animation_state;
}