#include "Ingame_Server.h"
#include "WWClient.h"


Ingame_Server::Ingame_Server() : sd(RakNet::SocketDescriptor(HOST_PORT, 0))
{
	//sd = new RakNet::SocketDescriptor(HOST_PORT,0);
	peer = RakNet::RakPeerInterface::GetInstance();
	peer->Startup(MAX_CLIENTS, &sd, 1);
	peer->SetMaximumIncomingConnections(MAX_CLIENTS);

	RakNet::BitStream bsOut;
	bsOut.Write((RakNet::MessageID)ID_GAME_MESSAGE_1);
	bsOut.Write("I'M THE HOST!!!!!!!!!!!!!");
	peer->Send(&bsOut,HIGH_PRIORITY,RELIABLE_ORDERED,0,WWClient::get()->getServerAddr(),false);

	//WWClient::get()->talkToServer("hey it's me");
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
	RakNet::BitStream bsOut;
	bsOut.Write((RakNet::MessageID)ID_GAME_MESSAGE_1);
	bsOut.Write("I'M THE HOST!!!!!!!!!!!!!");
	peer->Send(&bsOut,HIGH_PRIORITY,RELIABLE_ORDERED,0,WWClient::get()->getServerAddr(),false);
	//WWClient::get()->talkToServer("peer logic");
	RakNet::Packet * packet;
	for (packet=peer->Receive(); packet; peer->DeallocatePacket(packet), packet=peer->Receive())
	{
		WWClient::get()->talkToServer("for loop");
		switch (packet->data[0])
		{
		case ID_CONNECTION_REQUEST_ACCEPTED:
			{
				printf("Our connection request has been accepted.\n");

			}
			break;

				
		default: // Handle Events Here
			
			try
			{

			// will throw an error if not one of our events
				WWEvent * new_event = create_event(packet->data[0]);

				RakNet::BitStream bsIn(packet->data,packet->length,false);
				bsIn.IgnoreBytes(sizeof(RakNet::MessageID));

				new_event->unpackage(&bsIn);
				new_event->put_in_game();

			}
			// for if it isn't one of our Events
			catch (Zeni::Error&) 
			{}
			
			break;

		}

	}

}

void Ingame_Server::send(WWEvent * e)
{
	//Ingame_Peer::send(e);
	// do nothing for server
}