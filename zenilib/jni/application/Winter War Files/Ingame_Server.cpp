#include "Ingame_Server.h"


Ingame_Server::Ingame_Server()
{
	sd = new RakNet::SocketDescriptor(HOST_PORT,0);
	peer->Startup(MAX_CLIENTS, sd, 1);
	peer->SetMaximumIncomingConnections(MAX_CLIENTS);
}

Ingame_Server::~Ingame_Server()
{
	RakNet::RakPeerInterface::DestroyInstance(peer);
}

void Ingame_Server::start_peer()
{
	//host_addr = addr;
	//RakNet::Packet * packet;
	
}

void Ingame_Server::peer_logic()
{
	RakNet::Packet * packet;
	for (packet=peer->Receive(); packet; peer->DeallocatePacket(packet), packet=peer->Receive())
		{
			switch (packet->data[0])
			{
			case ID_CONNECTION_REQUEST_ACCEPTED:
				{
					printf("Our connection request has been accepted.\n");

				}
				break;


			case BUILDING:
				{
					RakNet::BitStream bsIn(packet->data,packet->length,false);
					bsIn.IgnoreBytes(sizeof(RakNet::MessageID));

					WWEvent * build_event = new Build_Event();
					build_event->unpackage(&bsIn);
					build_event->put_in_game();
				}
				break;

			default:
				printf("Message with identifier %i has arrived.\n", packet->data[0]);
				break;
			}

		}

}

void Ingame_Server::send(WWEvent * e)
{
	//Ingame_Peer::send(e);
	// do nothing for server
}