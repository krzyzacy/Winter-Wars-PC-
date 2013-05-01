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

Zeni::String Objective::get_message_to_display()
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

Objective* Destroy_Key_Enemy_Structures::get_next_Objective()
{
	return new Rescue_Your_Network();
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

bool Build_a_Healing_Pool::has_been_completed()
{
	return false;
}

bool Build_Other_Structures::has_been_completed()
{
	return false;
}

bool Throw_Snowball_At_Enemy::has_been_completed()
{
	return false;
}

bool Pack_Snowball::has_been_completed()
{
	return false;
}

bool Scoop_Snow::has_been_completed()
{
	return false;
}

bool Destroy_Structures::has_been_completed()
{
	return false;
}

bool Raise_Lower_Tiles::has_been_completed()
{
	return false;
}

bool Build_a_Chain_To_Tree::has_been_completed()
{
	return false;
}

bool Destroy_Key_Enemy_Structures::has_been_completed()
{
	return false;
}

bool Rescue_Your_Network::has_been_completed()
{
	return false;
}

bool Claim_The_Tree::has_been_completed()
{
	return false;
}

bool Defend_Your_Claim::has_been_completed()
{//represents win?
	return false;
}