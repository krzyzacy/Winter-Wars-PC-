

#include "Ingame_Client.h"


Ingame_Client::Ingame_Client()
{
	sd = new RakNet::SocketDescriptor;
	peer->Startup(MAX_CLIENTS, sd, 1);
}

Ingame_Client::~Ingame_Client()
{
	RakNet::RakPeerInterface::DestroyInstance(peer);
}

void Ingame_Client::start_peer(RakNet::SystemAddress addr)
{
	short host_port = addr.GetPort();
	peer->Connect("127.0.0.1", host_port, 0,0);
}

void Ingame_Client::send(WWEvent * e)
{
	Ingame_Peer::send(e);
}