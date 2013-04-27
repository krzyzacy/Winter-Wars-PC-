/*
	Winter Wars Team
	04/13/2013
*/

#include <zenilib.h>

#include "Lobby_State.h"



  Lobby_State::Lobby_State()
    : Widget_Gamestate(make_pair(Point2f(0.0f, 0.0f), Point2f(800.0f, 600.0f))),client_list(MAX_PLAYER_NUM),state(0)
  {
	  initialize();
	  color_to_int[GREEN] = 0xFF00FF00;
	  color_to_int[RED] = 0xFFFF0000;
	  color_to_int[BLUE] = 0xFF0000FF;
	  color_to_int[ORANGE] = 0xFFFF6600;

	  client_list[0].color = GREEN;
	  client_list[1].color = GREEN;
	  client_list[2].color = GREEN;
	  client_list[3].color = GREEN;


	  room_created = false;
	  room_status = 0;
	  teamIndex = GREEN;
	  isStarted = false;
	  
	  get_Game().joy_mouse.enabled = true;
  }

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
	RakNet::Packet * packet;
	RakNet::RakPeerInterface * peer = WWClient::get()->getPeer();
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
	WWClient::get()->init();
}

void Lobby_State::start_game(){

	vector<int> colors_(MAX_PLAYER_NUM);
	vector<Zeni::String> genders_(MAX_PLAYER_NUM);
	vector<int> controls_(MAX_PLAYER_NUM);
	vector<int> sensitivities_(MAX_PLAYER_NUM);

	for(int i = 0; i < MAX_PLAYER_NUM; i++)
	{
		WWClient::get()->start_game(server_addr);

		if(i < client_list.size())
		{
			colors_[i] = (int)client_list[i].color - 1;
		}
		else
		{
			colors_[i] = 0;
		}

		genders_[i] = "Boy";
		controls_[i] = 0;
		sensitivities_[i] = 5;
	}

	//get_Game().pop_state();
	get_Game().push_state(new Play_State_Base(genders_, colors_, controls_, sensitivities_, false, room_created, host_addr));
}

void Lobby_State::createRoom(){
	WWClient::get()->createRoom(server_addr, host_addr, self_addr, room_created, client_list);
}

void Lobby_State::searchRoom(){
	WWClient::get()->searchRoom(server_addr, host_addr, self_addr, room_status, client_list);
}

void Lobby_State::changeTeam(TEAM_INDEX newTeam){
	teamIndex = newTeam;
	WWClient::get()->changeTeam(server_addr, newTeam);
}