#include "Ingame_Server.h"


Ingame_Server::Ingame_Server()
{
	sd = new RakNet::SocketDescriptor(SERVER_PORT,0);
	peer->Startup(MAX_CLIENTS, sd, 1);
}

Ingame_Server::~Ingame_Server()
{
	RakNet::RakPeerInterface::DestroyInstance(peer);
}

void Ingame_Server::start_peer(RakNet::SystemAddress addr)
{
	peer->SetMaximumIncomingConnections(MAX_CLIENTS);


}

void Ingame_Server::send(WWEvent * e)
{
	//Ingame_Peer::send(e);
	// do nothing for server
}