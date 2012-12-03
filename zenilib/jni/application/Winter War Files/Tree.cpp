#include "Tree.h"
#include "Team.h"

Tree::Tree(Team *team, Tile* tile_,
				const Zeni::Point3f &base_) :
	Structure(team, tile_, base_)
{
}


Tree::~Tree(void)
{
}

void Tree::update(const float &time)
{

}

const model_key_t Tree::get_model_name() const 
{
	if (!owner)
		return "neutral_tree";

switch(owner->get_Team_Index())	{
	case BLUE:
		return ("blue_tree");
	case GREEN:
		return ("green_tree");
	case RED:
		return ("red_tree");
	case ORANGE:
		return ("orange_tree");
	default:
		return ("blue_tree");
		break;
	}
}