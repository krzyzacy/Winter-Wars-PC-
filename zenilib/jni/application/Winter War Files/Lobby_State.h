/*
	Winter Wars Team
	04/13/2013
*/

#ifndef LOBBY_STATE_H
#define LOBBY_STATE_H

#include <zenilib.h>

#include "Play_State_Base.h"

#include "String.h"
#include <vector>
#include "Team.h"

#include <stdio.h>
#include <string.h>
#include "RakPeerInterface.h"
#include "MessageIdentifiers.h"
#include "BitStream.h"
#include "RakNetTypes.h"  // MessageID
#include <vector>
#include <map>

using namespace std;
using namespace Zeni;

#define MAX_CLIENTS 10
#define SERVER_PORT 60000
#define MAX_PLAYER_NUM 4

struct Client
{
	RakNet::SystemAddress ip_addr;
	TEAM_INDEX color;
};

class Lobby_State : public Widget_Gamestate {
  Lobby_State(const Lobby_State &);

public:
  Lobby_State()
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
  ~Lobby_State(){
	  RakNet::RakPeerInterface::DestroyInstance(peer);
  }

private:

  map<TEAM_INDEX, Uint32> color_to_int; 

  int state;
  RakNet::RakPeerInterface * peer;
  RakNet::Packet * packet;
  RakNet::SocketDescriptor sd;

  bool room_created;
  int room_status;
  TEAM_INDEX teamIndex;
  vector<Client> client_list;
  RakNet::SystemAddress server_addr;

  RakNet::SystemAddress host_addr;
  RakNet::SystemAddress self_addr;
  bool isStarted;

  void render_controls(int y){}
  void on_pop() {get_Game().joy_mouse.enabled = true;}

  void on_key(const SDL_KeyboardEvent &event);

  void on_joy_button(const SDL_JoyButtonEvent &event);

  void perform_logic();

  void initialize();

  void start_game();

  void createRoom();

  void searchRoom();

  void changeTeam(TEAM_INDEX newTeam);

  void render();
};

#endif
