/*
	Ingame_Client.h
	Winter Wars peer-to-peer client
	04/14/2013
*/

#ifndef INGAME_CLIENT_H
#define INGAME_CLIENT_H


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

class Ingame_Client: public Ingame_Peer
{

public:
	Ingame_Client();
	~Ingame_Client();

	virtual void start_peer(RakNet::SystemAddress addr);
	virtual void send(WWEvent * e);

};

#endif