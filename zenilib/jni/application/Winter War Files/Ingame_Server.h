/*
	Ingame_Server.h
	Winter Wars peer-to-peer server
	04/14/2013
*/

#ifndef INGAME_SERVER_H
#define INGAME_SERVER_H

#include <zenilib.h>

#include "Ingame_Peer.h"
#include "Utility.h"

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

#include <pthread.h>

class Ingame_Server: public Ingame_Peer
{

public:
	Ingame_Server();
	~Ingame_Server();

	
	virtual void start_peer(RakNet::SystemAddress addr);
	virtual void send(WWEvent * e);

};




#endif