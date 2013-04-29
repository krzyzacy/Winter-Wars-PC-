
#include <zenilib.h>
#include "WWClient.h"

WWClient* WWClient::wwInstance = 0;

WWClient::~WWClient()
{
	RakNet::RakPeerInterface::DestroyInstance(peer);
}

WWClient* WWClient::get(){

	if(wwInstance == 0){
		wwInstance = new WWClient;
	}
	return wwInstance;
}

void WWClient::init(){
	peer = RakNet::RakPeerInterface::GetInstance();  
	peer->Startup(2,&sd, 1);
	peer->Connect("127.0.0.1", SERVER_PORT, 0,0);
	//peer->Connect("127.0.0.1", HOST_PORT, 0,0);
}

void WWClient::createRoom(RakNet::SystemAddress &server_addr, RakNet::SystemAddress &host_addr, 
	                      RakNet::SystemAddress &self_addr, bool &room_created, vector<Client> client_list){
	char str[512];

	while (1)
	{
		for (packet=peer->Receive(); packet; peer->DeallocatePacket(packet), packet=peer->Receive())
		{
			switch (packet->data[0])
			{
			case ID_CONNECTION_REQUEST_ACCEPTED:
				{
					printf("Our connection request has been accepted.\n");

					// Use a BitStream to write a custom user message
					// Bitstreams are easier to use than sending casted structures, and handle endian swapping automatically
					RakNet::BitStream bsOut;
					bsOut.Write((RakNet::MessageID)CREATE_ROOM);
					bsOut.Write("CREATE A NEW GAME ROOM");
					peer->Send(&bsOut,HIGH_PRIORITY,RELIABLE_ORDERED,0,packet->systemAddress,false);

					server_addr = packet->systemAddress;
				}
				break;
			case ID_NO_FREE_INCOMING_CONNECTIONS:
				printf("The server is full.\n");
				break;
			case ID_DISCONNECTION_NOTIFICATION:
				printf("We have been disconnected.\n");
				break;
			case ID_CONNECTION_LOST:
				printf("Connection lost.\n");
				break;

			case CREATE_ROOM:
				{
					room_created = true;

					RakNet::BitStream bsIn(packet->data,packet->length,false);
					bsIn.IgnoreBytes(sizeof(RakNet::MessageID));
					bsIn.Read(host_addr);

					self_addr = host_addr;

					Client host;
					host.ip_addr = host_addr;
					host.color = GREEN;
					client_list[0] = host;

					RakNet::BitStream bsOut;
					bsOut.Write((RakNet::MessageID)ID_GAME_MESSAGE_1);
					bsOut.Write("ROOM CREATED");
					peer->Send(&bsOut,HIGH_PRIORITY,RELIABLE_ORDERED,0,packet->systemAddress,false);
				}
				break;


			default:
				printf("Message with identifier %i has arrived.\n", packet->data[0]);
				break;
			}

			if(room_created) break;
		}
		if(room_created) break;
	}


}

void WWClient::searchRoom(RakNet::SystemAddress &server_addr, RakNet::SystemAddress &host_addr, 
	                      RakNet::SystemAddress &self_addr, int &room_status, vector<Client> client_list)
{
	char str[512];

	while (1)
	{
		for (packet=peer->Receive(); packet; peer->DeallocatePacket(packet), packet=peer->Receive())
		{
			switch (packet->data[0])
			{
			case ID_CONNECTION_REQUEST_ACCEPTED:
				{
					printf("Our connection request has been accepted.\n");

					// Use a BitStream to write a custom user message
					// Bitstreams are easier to use than sending casted structures, and handle endian swapping automatically
					RakNet::BitStream bsOut;
					bsOut.Write((RakNet::MessageID)SEARCH_ROOM);
					bsOut.Write("Search for an existing game room");
					peer->Send(&bsOut,HIGH_PRIORITY,RELIABLE_ORDERED,0,packet->systemAddress,false);

					server_addr = packet->systemAddress;
				}
				break;
			case ID_NO_FREE_INCOMING_CONNECTIONS:
				printf("The server is full.\n");
				break;
			case ID_DISCONNECTION_NOTIFICATION:
				printf("We have been disconnected.\n");
				break;
			case ID_CONNECTION_LOST:
				printf("Connection lost.\n");
				break;


			case SEARCH_ROOM:
				{
					room_status = 1;

					int num_client;
					RakNet::SystemAddress temp_addr;

					Client client;
					RakNet::BitStream bsIn(packet->data,packet->length,false);
					bsIn.IgnoreBytes(sizeof(RakNet::MessageID));
					bsIn.Read(num_client);
					bsIn.Read(temp_addr);

					//int num_client = rs.GetLength();
					for(int i = 0; i < num_client; i ++)
					{
						bsIn.Read(client);
						client_list[i] = client;
					}

					host_addr = client_list[0].ip_addr;
					self_addr = temp_addr;

					RakNet::BitStream bsOut;
					bsOut.Write((RakNet::MessageID)ID_GAME_MESSAGE_1);
					bsOut.Write(self_addr.ToString());
					peer->Send(&bsOut,HIGH_PRIORITY,RELIABLE_ORDERED,0,packet->systemAddress,false);
				}
			break;

			case NO_ROOM:
				{
					room_status = -1;
				}
			break;

			default:
				printf("Message with identifier %i has arrived.\n", packet->data[0]);
				break;
			}

			if(room_status != 0) break;
		}
		if(room_status != 0) break;
	}
}

void WWClient::changeTeam(RakNet::SystemAddress server_addr, TEAM_INDEX newTeam)
{
	RakNet::BitStream bsOut;
	bsOut.Write((RakNet::MessageID)TEAM_CHANGE);
	bsOut.Write(newTeam);
	peer->Send(&bsOut,HIGH_PRIORITY,RELIABLE_ORDERED,0,server_addr,false);
}

void WWClient::start_game(RakNet::SystemAddress server_addr)
{
	this->server_addr = server_addr;
	RakNet::BitStream bsOut;
	bsOut.Write((RakNet::MessageID)START_GAME);
	peer->Send(&bsOut,HIGH_PRIORITY,RELIABLE_ORDERED,0,server_addr,false);
}

void WWClient::send(WWEvent *e)
{
	talkToServer(host_addr.ToString());

	// I need to delete bsOut since package new's it
	RakNet::BitStream *bsOut = e->package();
	peer->Send(bsOut,HIGH_PRIORITY,RELIABLE_ORDERED,0,server_addr,false);

	delete bsOut;
}

void WWClient::talkToServer(const char * msg)
{
	RakNet::BitStream bsOut;
	bsOut.Write((RakNet::MessageID)ID_GAME_MESSAGE_1);
	bsOut.Write(msg);
	peer->Send(&bsOut,HIGH_PRIORITY,RELIABLE_ORDERED,0,server_addr,false);
}

void WWClient::WWhost_logic()
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

		default: // Handle Events Here
			
			try
			{

			// will throw an error if not one of our events
				WWEvent * new_event = create_event(packet->data[0]);

				RakNet::BitStream bsIn(packet->data,packet->length,false);
				bsIn.IgnoreBytes(sizeof(RakNet::MessageID));

				new_event->unpackage(&bsIn);
				new_event->put_in_game();

				delete new_event;

			}
			// for if it isn't one of our Events
			catch (Zeni::Error&) 
			{}
			
			break;

		}
	}

}

void WWClient::connect_to_host()
{
	peer->Connect("127.0.0.1", host_addr.GetPort(), 0, 0);

}

RakNet::SystemAddress WWClient::get_my_address()
{
	return peer->GetSystemAddressFromGuid(peer->GetMyGUID());
}
