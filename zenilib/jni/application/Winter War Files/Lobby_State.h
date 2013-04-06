#include <zenilib.h>

#include "Controls.h"
#include "View.h"
#include "Player.h"
#include "Player_View.h"
#include "Permanent.h"

#include "Play_State_Base.h"

#include "String.h"
#include <vector>
#include "Team.h"
#include "Object_factory.h"

#include <stdio.h>
#include <string.h>
#include "RakPeerInterface.h"
#include "MessageIdentifiers.h"
#include "BitStream.h"
#include "RakNetTypes.h"  // MessageID

using namespace std;
using namespace Zeni;

#define MAX_CLIENTS 10
#define SERVER_PORT 60000

class Lobby_State : public Widget_Gamestate {
  Lobby_State(const Lobby_State &);
  Lobby_State operator=(const Lobby_State &);

public:
  Lobby_State()
    : Widget_Gamestate(make_pair(Point2f(0.0f, 0.0f), Point2f(800.0f, 600.0f)))
  {
	  initialize();
	  state = 0;
	  room_created = false;
	  get_Game().joy_mouse.enabled = true;
  }
  ~Lobby_State(){
	  RakNet::RakPeerInterface::DestroyInstance(peer);
  }

private:
  int state;
  RakNet::RakPeerInterface * peer;
  RakNet::Packet * packet;
  RakNet::SocketDescriptor sd;

  bool room_created;

  void render_controls(int y){}
  void on_pop() {get_Game().joy_mouse.enabled = true;}

  void on_key(const SDL_KeyboardEvent &event);

  void on_joy_button(const SDL_JoyButtonEvent &event);

  void initialize();

  void createRoom();

  void searchRoom();

  void render();
};