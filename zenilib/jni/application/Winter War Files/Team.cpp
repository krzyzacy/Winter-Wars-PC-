#include "Team.h"
#include "World.h"
#include "Player.h"
#include "Game_Model.h"


using namespace std;
using namespace Zeni;


Team::Team(Tile* BaseTile)	:
	Base(BaseTile), Ice_Blocks(0), intake_rate(0.0f)
{
}


Team::~Team(void)
{
}

void Team::add_player(Player *p)	{
	members.push_back(p);
}

