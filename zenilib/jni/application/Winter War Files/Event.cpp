
#include "Event.h"
#include "WWClient.h"
#include  "Player.h"
#include "Structure.h"
#include "Team.h"
#include "Ingame_Peer.h"

#include "MessageIdentifiers.h"
#include "Object_factory.h"
#include "Game_Model.h"
#include "World.h"
#include "Snowball.h"


#include "MessageIdentifiers.h"

using namespace Zeni;

WWEvent::WWEvent()
{
}

void WWEvent::send_me()
{
	if (WWClient::isNetwork())
		WWClient::get()->send(this);
}


WWEvent *create_event(unsigned char event_type)
{
	switch (DefaultMessageIDTypes(event_type))
	{
		case BUILDING:
			return new Build_Event;
		case PLAYER_MOVEMENT:
			return new Player_Movement_Event;
		case THROW_SNOWBALL:
			return new Throw_Snowball_Event;


		default:
			throw Error("Not An Event");
	};
}

/*
	BUILD
*/

Build_Event::Build_Event(Structure *snowman)
	: type(snowman->get_type()), tile(snowman->get_top_center()), team_color(snowman->get_team_pt()->get_Team_Index())
{
	send_me();
}

RakNet::BitStream *Build_Event::package()
{
	RakNet::BitStream *bsOut = new RakNet::BitStream;		
	bsOut->Write((RakNet::MessageID)BUILDING);

	bsOut->Write(type );

	bsOut->Write(tile.x);	
	bsOut->Write(tile.y);

	bsOut->Write(team_color);

	return bsOut;
}

void Build_Event::unpackage(RakNet::BitStream *bsIn)
{
	WWClient::get()->talkToServer("Build event");

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

void Build_Event::put_in_game(int row, int col, int team_, int type_)
{
	//Game_Model::get().get_team(team_ - 1)->add_tile(Game_Model::get().get_World()->get_tile(row, col));
	create_structure(type_, Game_Model::get().get_World()->get_tile(row, col),
						Game_Model::get().get_team(team_ - 1));
}

/*
	PLAYER MOVEMENT
*/

Player_Movement_Event::Player_Movement_Event(Player * _player)
	: player_num(0),
	position(_player->get_position()),
	velocity(_player->get_velocity()),
	team_color(_player->get_Team_Index())
{
	send_me();
}

RakNet::BitStream *Player_Movement_Event::package()
{
	RakNet::BitStream *bsOut = new RakNet::BitStream;
	
	bsOut->Write((RakNet::MessageID)PLAYER_MOVEMENT);

	bsOut->Write(player_num);

	bsOut->Write(position.x);
	bsOut->Write(position.y);
	bsOut->Write(position.z);

	bsOut->Write(velocity.x);
	bsOut->Write(velocity.y);
	bsOut->Write(velocity.z);

	bsOut->Write(team_color);

	return bsOut;
}

void Player_Movement_Event::unpackage(RakNet::BitStream *bsIn)
{	
	WWClient::get()->talkToServer("move receive event");

	bsIn->Read(player_num);

	bsIn->Read(position.x);
	bsIn->Read(position.y);
	bsIn->Read(position.z);

	bsIn->Read(velocity.x);
	bsIn->Read(velocity.y);
	bsIn->Read(velocity.z);

	bsIn->Read(team_color);
}

void Player_Movement_Event::put_in_game()
{
	//This will have to change because we will have to store stuff differently
	Player* p = Game_Model::get().get_player(1);
	p->network_overwrite_members(position, velocity);
}

/*
	Throw_Snowball_Event
*/

Throw_Snowball_Event::Throw_Snowball_Event(Player *p, 
		const Zeni::Point3f &pos_,
		const Zeni::Vector3f &velo_,
		float rad)
	: player_num(1), pos(pos_), velo(velo_), radius(rad)
{
	send_me();
}

RakNet::BitStream *Throw_Snowball_Event::package()
{
	RakNet::BitStream *bsOut = new RakNet::BitStream;		
	bsOut->Write((RakNet::MessageID)THROW_SNOWBALL);

	bsOut->Write(player_num );

	bsOut->Write(pos.x);	
	bsOut->Write(pos.y);	
	bsOut->Write(pos.z);

	bsOut->Write(velo.x);	
	bsOut->Write(velo.y);	
	bsOut->Write(velo.z);

	bsOut->Write(radius);

	return bsOut;
}

void Throw_Snowball_Event::unpackage(RakNet::BitStream *bsIn)
{
	WWClient::get()->talkToServer("Snowball event");
	
	bsIn->Read(player_num );

	bsIn->Read(pos.x);	
	bsIn->Read(pos.y);	
	bsIn->Read(pos.z);

	bsIn->Read(velo.x);	
	bsIn->Read(velo.y);	
	bsIn->Read(velo.z);

	bsIn->Read(radius);	
}

void Throw_Snowball_Event::put_in_game()
{	
	// in the future we should account for delay, 
	// calculate where it should be on the computer it was sent.

	Snowball *sb = new Snowball(Game_Model::get().get_player(player_num),
		pos, Vector3f(radius, radius, radius));

	sb->get_thrown(velo);

	Game_Model::get().add_moveable(sb);
}


