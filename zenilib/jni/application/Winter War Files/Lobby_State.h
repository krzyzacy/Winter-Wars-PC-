/*
	Winter Wars Team
	04/13/2013
*/

#ifndef LOBBY_STATE_H
#define LOBBY_STATE_H

#include <zenilib.h>
#include "WWClient.h"
#include "Play_State_Base.h"

#include "String.h"

#include <stdio.h>
#include <string.h>
#include <map>

using namespace std;
using namespace Zeni;

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
	  
  }

private:

  map<TEAM_INDEX, Uint32> color_to_int; 

  int state;

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
