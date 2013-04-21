/*
	Ingame_Server.h
	Winter Wars peer-to-peer server
	04/14/2013
*/

#ifndef INGAME_SERVER_H
#define INGAME_SERVER_H

#include <zenilib.h>

//#include "Ingame_Peer.h"
#include "Utility.h"
#include "Event.h"

#include "String.h"
#include <vector>

#include <stdio.h>
#include <string.h>
#include "RakPeerInterface.h"
#include "MessageIdentifiers.h"
#include "BitStream.h"
#include "RakNetTypes.h"  // MessageID
#include <vector>
#include <map>

class Ingame_Server
{

public:
	Ingame_Server();
	~Ingame_Server();

	
	virtual void start_peer();
	virtual void send(WWEvent * e);

	virtual void peer_logic();

private:
	RakNet::RakPeerInterface * peer;
	RakNet::SocketDescriptor * sd;

};




#endif