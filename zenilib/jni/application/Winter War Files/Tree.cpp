#include "Tree.h"
#include "Team.h"
using namespace Zeni;

#include "Game_Model.h"

Tree::Tree(Team *team, Tile* tile_,
				const Zeni::Point3f &base_) :
	Structure(team, tile_, base_, 200),nyan(new Zeni::Sound_Source(Zeni::get_Sounds()["NyanCat"]))
{	
	if (!owner){
		animation_state = new Tree_unowned();
		nyan->stop();
	}
	else{
		animation_state = new Tree_owned();

		if(!nyan->is_playing())
			nyan->play();

	}

	center.z += 60;

	Game_Model::get().tree_claimed(owner);
}


Tree::~Tree(void)
{
	nyan->stop();
}

void Tree::update(const float &time)
{
	// if being removed from network
	if(Isolation_Clock.seconds() > 0)
	{
		Isolation_Clock.reset();
		Isolation_Clock.stop();

		owner->remove_tile(hex);
		nyan->stop();
		// reset to neutral
		owner = 0;
		Game_Model::get().tree_claimed(0);
		animation_state = new Tree_unowned();
	}
}

void Tree::destabilize_network()	{
	if(owner)
		owner->destabilize_network();
}

void Tree::handle_player_collision(Player *P)	{
	//DO NOTHING
}

void Tree::create_body()	{
	body = Zeni::Collision::Capsule(center + Vector3f(0,0,1), center - Vector3f(0,0,-1), 0.05);

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