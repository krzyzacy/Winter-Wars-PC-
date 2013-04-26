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


			case BUILDING:
				{
					WWClient::get()->talkToServer("receiving event");

					RakNet::BitStream bsIn(packet->data,packet->length,false);
					bsIn.IgnoreBytes(sizeof(RakNet::MessageID));

					WWEvent * build_event = new Build_Event();
					build_event->unpackage(&bsIn);
					build_event->put_in_game();
				}
				break;

			case PLAYER_MOVEMENT:
				{
					WWClient::get()->talkToServer("move receive event");

					RakNet::BitStream bsIn(packet->data, packet->length, false);
					bsIn.IgnoreBits(sizeof(RakNet::MessageID));

					WWEvent * player_move = new Player_Movement_Event();
					player_move->unpackage(&bsIn);
					player_move->put_in_game();
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