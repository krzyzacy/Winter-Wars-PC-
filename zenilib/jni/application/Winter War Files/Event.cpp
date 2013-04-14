
#include "Event.h"

#include  "Player.h"
#include "Structure.h"
#include "Team.h"
#include "Ingame_Peer.h"

#include "Object_factory.h"
#include "Game_Model.h"
#include "World.h"

using namespace Zeni;

Build_Event::Build_Event(Structure *snowman)
	: type(SNOWMAN), tile(snowman->get_top_center()), team_color(snowman->get_team_pt()->get_Team_Index())
{

}

RakNet::BitStream *Build_Event::package()
{
	RakNet::BitStream *bsOut = new RakNet::BitStream;		
	bsOut->Write((RakNet::MessageID)170);

	bsOut->Write(type );

	bsOut->Write(tile.x);	
	bsOut->Write(tile.y);

	bsOut->Write(team_color);

	return bsOut;
}

void Build_Event::unpackage(RakNet::BitStream *bsIn)
{
	bsIn->IgnoreBytes(sizeof(RakNet::MessageID));
	
	bsIn->Read(type );

	bsIn->Read(tile.x);	
	bsIn->Read(tile.y);

	bsIn->Read(team_color);
}

void Build_Event::put_in_game()
{
	create_structure(type, Game_Model::get().get_World()->get_tile(tile),
						Game_Model::get().get_team(team_color - 1));
}