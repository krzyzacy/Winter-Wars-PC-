
#include <zenilib.h>

#include "RakPeerInterface.h"
#include "MessageIdentifiers.h"
#include "BitStream.h"
#include "RakNetTypes.h"
#include "Team.h"
#include "Event.h"

#include <vector>

using namespace std;

#define MAX_CLIENTS 10
#define SERVER_PORT 60000
#define MAX_PLAYER_NUM 4

struct Client
{
	RakNet::SystemAddress ip_addr;
	TEAM_INDEX color;
};

class WWClient
{
	public:
		~WWClient();
		static WWClient* get();
		void init();
		void createRoom(RakNet::SystemAddress &server_addr, RakNet::SystemAddress &host_addr, 
	                    RakNet::SystemAddress &self_addr, bool &room_created, vector<Client> client_list);
		void searchRoom(RakNet::SystemAddress &server_addr, RakNet::SystemAddress &host_addr, 
	                      RakNet::SystemAddress &self_addr, int &room_status, vector<Client> client_list);
		void changeTeam(RakNet::SystemAddress server_addr, TEAM_INDEX newTeam);
		void start_game(RakNet::SystemAddress server_addr);
		//bool update_team();
		RakNet::RakPeerInterface * getPeer() {return peer;}
		void setHostAddr(RakNet::SystemAddress host_addr_){ 
			//host_addr = host_addr_;
			host_addr.CopyPort(host_addr_);
		}
		void send(WWEvent *e);

	private:
		static WWClient* wwInstance; 
		RakNet::SystemAddress host_addr;
		RakNet::RakPeerInterface * peer;
		RakNet::Packet * packet;
		RakNet::SocketDescriptor sd;

	

};