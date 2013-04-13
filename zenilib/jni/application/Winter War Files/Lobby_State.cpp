/*
	Winter Wars Team
	04/13/2013
*/


#include "Lobby_State.h"



enum GameMessages
{
	ID_GAME_MESSAGE_1 = ID_USER_PACKET_ENUM + 1,
	CREATE_ROOM,
	SEARCH_ROOM,
	NO_ROOM,
	TEAM_CHANGE,
	START_GAME
};

void Lobby_State::on_key(const SDL_KeyboardEvent &event) {
	if(event.keysym.sym == SDLK_ESCAPE && event.state == SDL_PRESSED)
		get_Game().pop_state();
	if(event.keysym.sym == SDLK_a && event.state == SDL_PRESSED)
	{
		if(!room_created && room_status == 0)
			createRoom();
	}
	if(event.keysym.sym == SDLK_b && event.state == SDL_PRESSED)
	{
		if(!room_created && room_status == 0)
			searchRoom();
	}

	if(event.keysym.sym == SDLK_UP && event.state == SDL_PRESSED)
		changeTeam( (TEAM_INDEX)(((int)teamIndex + 1) % 4));

	if(event.keysym.sym == SDLK_DOWN && event.state == SDL_PRESSED)
		changeTeam( (TEAM_INDEX)(((int)teamIndex + 3) % 4));

	if(event.keysym.sym == SDLK_RETURN && event.state == SDL_PRESSED){
		if(room_created) {
			isStarted = true;
			start_game();
		}
	}

}

void Lobby_State::on_joy_button(const SDL_JoyButtonEvent &event) {
	switch(event.button){
		case 0: // A
			break;

		case 1: // B
			break;
				
		default:
			break;
	}
}

void Lobby_State::perform_logic(){
	if(room_status == 1 || room_created){

		
		
		for (packet=peer->Receive(); packet; peer->DeallocatePacket(packet), packet=peer->Receive())
			{
				switch (packet->data[0])
				{
					case TEAM_CHANGE:
					{

						int num_client;

						Client client;
						RakNet::BitStream bsIn(packet->data,packet->length,false);
						bsIn.IgnoreBytes(sizeof(RakNet::MessageID));
						bsIn.Read(num_client);
						
						//int num_client = rs.GetLength();
						for(int i = 0; i < num_client; i ++)
						{
							bsIn.Read(client);
							client_list[i] = client;
						}
					}
					break;

					case START_GAME:
					{
						if(!isStarted){
							isStarted = true;
							start_game();
						}
					}
					break;

					default:
					printf("Message with identifier %i has arrived.\n", packet->data[0]);
					break;
				}
		}
	}
}

void Lobby_State::render() {
	Widget_Gamestate::render();
	get_Fonts()["system_36_800x600"].render_text("Game Lobby v0.0" ,Point2f(155, 60), Color(0xFF33BBE8));
	if(!room_created && !room_status){
		get_Fonts()["system_36_800x600"].render_text("A to create a new game" ,Point2f(100, 180), Color(0xFF33BBE8));
		get_Fonts()["system_36_800x600"].render_text("B to searching for games" ,Point2f(100, 250), Color(0xFF33BBE8));
	}
	else if(room_created){

		get_Fonts()["system_36_800x600"].render_text("ROOM CREATED" ,Point2f(155, 160), Color(0xFF33BBE8));

		get_Fonts()["system_36_800x600"].render_text(self_addr.ToString() ,Point2f(70, 190), Color(color_to_int[teamIndex]));
		int counter = 0;
		for(int i = 0; i < client_list.size(); i++){
			if(client_list[i].ip_addr == self_addr)
				continue;
			else
				counter++;

			get_Fonts()["system_36_800x600"].render_text(client_list[i].ip_addr.ToString() ,Point2f(70, 190 + counter * 30), Color(color_to_int[client_list[i].color]));
		}
	}
	else if(room_status == 1){  // join game
		get_Fonts()["system_36_800x600"].render_text("Joined Game" ,Point2f(155, 160), Color(0xFF33BBE8));

		get_Fonts()["system_36_800x600"].render_text(self_addr.ToString() ,Point2f(70, 190), Color(color_to_int[teamIndex]));
		int counter = 0;
		for(int i = 0; i < client_list.size(); i++){
			if(client_list[i].ip_addr == self_addr)
				continue;
			else
				counter++;

			get_Fonts()["system_36_800x600"].render_text(client_list[i].ip_addr.ToString() ,Point2f(70, 190 + counter * 30), Color(color_to_int[client_list[i].color]));
		}
	}
	else if(room_status == -1){
		get_Fonts()["system_36_800x600"].render_text("No Game Available" ,Point2f(155, 160), Color(0xFF33BBE8));
	}
	//get_Video().set_2d(make_pair(Point2f(0.0f, 0.0f), Point2f(1920.0f, 1200.0f)), true);
	//render_image("ts800", Point2f(0.0f,0.0f), Point2f(1024.0f, 1024.0f));
	render_controls(0);
}

void Lobby_State::initialize(){
	peer = RakNet::RakPeerInterface::GetInstance();  
	peer->Startup(1,&sd, 1);
	peer->Connect("127.0.0.1", SERVER_PORT, 0,0);
}

void Lobby_State::start_game(){

	vector<int> colors_(MAX_PLAYER_NUM);
	vector<Zeni::String> genders_(MAX_PLAYER_NUM);
	vector<int> controls_(MAX_PLAYER_NUM);
	vector<int> sensitivities_(MAX_PLAYER_NUM);

	for(int i = 0; i < MAX_PLAYER_NUM; i++)
	{
		RakNet::BitStream bsOut;
		bsOut.Write((RakNet::MessageID)START_GAME);
		bsOut.Write(i);
		peer->Send(&bsOut,HIGH_PRIORITY,RELIABLE_ORDERED,0,server_addr,false);

		if(i < client_list.size())
		{
			colors_[i] = client_list[i].color;
		}
		else
		{
			colors_[i] = GREEN;
		}

		genders_[i] = "Boy";
		controls_[i] = 0;
		sensitivities_[i] = 5;
	}

	//get_Game().pop_state();
	get_Game().push_state(new Play_State_Base(genders_, colors_, controls_, sensitivities_));
}

void Lobby_State::createRoom(){
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

void Lobby_State::searchRoom(){
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

void Lobby_State::changeTeam(TEAM_INDEX newTeam){
	teamIndex = newTeam;

	RakNet::BitStream bsOut;
	bsOut.Write((RakNet::MessageID)TEAM_CHANGE);
	bsOut.Write(newTeam);
	peer->Send(&bsOut,HIGH_PRIORITY,RELIABLE_ORDERED,0,server_addr,false);
}