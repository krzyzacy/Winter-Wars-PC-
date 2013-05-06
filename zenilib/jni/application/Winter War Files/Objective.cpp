#include "Objective.h"
#include "Game_Model.h"

#include "Player.h"
#include "Team.h"
#include "Structure.h"
#include "Object_factory.h"
#include "Tile.h"
#include "Event.h"
#include "Snowball.h"

using namespace std;
using namespace Zeni;

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
	return new Build_Structure(HEALING_POOL);
}

Objective* Build_Structure::get_next_Objective()
{
	//return new Scoop_Snow();
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

bool Build_Structure::has_been_completed()
{
	if (Game_Model::get().get_player(0)->get_team()->stats.structures[type]){
		return true;
	}
		

	return false;
}

bool Build_Other_Structures::has_been_completed()
{	
	if (Game_Model::get().get_player(0)->get_team()->stats.structures[HEALING_POOL]
	&& Game_Model::get().get_player(0)->get_team()->stats.structures[FORT]
	&& Game_Model::get().get_player(0)->get_team()->stats.structures[SNOWMAN]
	&& Game_Model::get().get_player(0)->get_team()->stats.structures[SNOW_FACTORY]
	)
		return true;

	return false;
}

Throw_Snowball_At_Enemy::Throw_Snowball_At_Enemy()
{
	message = "Throw Snowballs with right trigger to defeat enemies!";
	Game_Model::get().add_player(create_player(Game_Model::get().get_team(RED-1), "Boy"
		));//, Game_Model::get().get_tile(Point3f(100,100,0))));


	for(int i = 0; i < 10; i++){
		for(int j = 0; j < 10; j++){
			Snowball *sb = new Snowball(Game_Model::get().get_player(1),
				Point3f(50 * (i + 5), 50 * (j + 5), 1000), Vector3f(20, 20, 20));

			sb->get_thrown(Vector3f(0, 0, 0));

			Game_Model::get().add_moveable(sb);
		}
	}
}

bool Throw_Snowball_At_Enemy::has_been_completed()
{
	if (Game_Model::get().get_player(0)->stats.damage_dealt 
		&& Game_Model::get().get_player(1)->stats.damage_taken)
		return true;

	return false;
}

bool Pack_Snowball::has_been_completed()
{
	if (Game_Model::get().get_player(0)->stats.num_large_snowballs)
		return true;

	return false;
}

Scoop_Snow::Scoop_Snow() :
	start_scooped(Game_Model::get().get_player(0)->stats.amount_scooped)
{
	message = "Hold B to scoop up snow, you must be on a soft snow tile";
}

bool Scoop_Snow::has_been_completed()
{
	if (Game_Model::get().get_player(0)->stats.amount_scooped > start_scooped)
		return true;

	return false;
}

Destroy_Structures::Destroy_Structures()
{
	message = "Destroy Enemy Stuctures by shooting snowballs at them";

	Build_Event ev;
	
	ev.put_in_game(10,12,2,3);
}

bool Destroy_Structures::has_been_completed()
{
	return (Game_Model::get().get_tile(10, 12)->has_building() ^ 0x1);
	//return false;
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