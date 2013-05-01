#include "Objective.h"
#include "Game_Model.h"

using namespace std;

Objective::Objective()
{
	message = "This string should never be seen";
}

Objective::~Objective()
{};

bool Objective::has_been_completed()
{	//Always returns false becuase base class is abstract
	return false;
}

string Objective::get_message_to_display()
{
	return message;
}

Objective* Objective::get_next_Objective()
{
	return new Build_a_Healing_Pool();
}

Objective* Build_a_Healing_Pool::get_next_Objective()
{
	return new Build_Other_Structures();
}

Objective* Build_Other_Structures::get_next_Objective()
{
	return new Throw_Snowball_At_Enemy();
}

Objective* Throw_Snowball_At_Enemy::get_next_Objective()
{
	return new Pack_Snowball();
}

Objective* Pack_Snowball::get_next_Objective()
{
	return new Scoop_Snow();
}

Objective* Scoop_Snow::get_next_Objective()
{
	return new Destroy_Structures();
}

Objective* Destroy_Structures::get_next_Objective()
{
	return new Raise_Lower_Tiles();
}

Objective* Raise_Lower_Tiles::get_next_Objective()
{
	return new Build_a_Chain_To_Tree();
}

Objective* Build_a_Chain_To_Tree::get_next_Objective()
{
	return new Destroy_Key_Enemy_Structures();
}

Objective* Rescue_Your_Network::get_next_Objective()
{
	return new Claim_The_Tree();
}

Objective* Claim_The_Tree::get_next_Objective()
{
	return new Defend_Your_Claim();
}

Objective* Defend_Your_Claim::get_next_Objective()
{//represents win?
	return NULL;
}


