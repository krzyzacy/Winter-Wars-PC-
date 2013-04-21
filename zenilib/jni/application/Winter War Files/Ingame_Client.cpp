

#include "Ingame_Client.h"


Ingame_Client::Ingame_Client()
{
	sd = new RakNet::SocketDescriptor;
	peer->Startup(1, sd, 1);
}

Ingame_Client::~Ingame_Client()
{
	RakNet::RakPeerInterface::DestroyInstance(peer);
}

void Ingame_Client::start_peer(RakNet::SystemAddress addr)
{
	host_addr = addr;

	RakNet::Packet * packet;
	short host_port = addr.GetPort();
	peer->Connect("127.0.0.1", host_port, 0,0);

	while (1)
	{
		for (packet=peer->Receive(); packet; peer->DeallocatePacket(packet), packet=peer->Receive())
		{
			switch (packet->data[0])
			{
			case ID_CONNECTION_REQUEST_ACCEPTED:
				{
					printf("Our connection request has been accepted.\n");

				}
				break;
			
			
			default:
				printf("Message with identifier %i has arrived.\n", packet->data[0]);
				break;
			}
		}
	}
}

void Ingame_Client::send(WWEvent * e)
{
	peer->Send(e->package(),HIGH_PRIORITY,RELIABLE_ORDERED,0,host_addr,false);
}