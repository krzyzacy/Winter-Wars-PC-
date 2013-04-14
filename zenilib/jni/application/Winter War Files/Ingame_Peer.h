/*
	Ingame_Peer.h
	Winter Wars peer-to-peer interface
	04/14/2013
*/

#pragma once

#ifndef INGAME_PEER_H
#define INGAME_PEER_H

#include <zenilib.h>

#include "Play_State_Base.h"

#include "String.h"
#include <vector>

#include <stdio.h>
#include <string.h>
#include "Event.h"
#include "RakPeerInterface.h"
#include "MessageIdentifiers.h"
#include "BitStream.h"
#include "RakNetTypes.h"  // MessageID
#include <vector>
#include <map>

class Ingame_Peer{

public:
	Ingame_Peer() {} 
	virtual ~Ingame_Peer() {}


	RakNet::RakPeerInterface * peer;
	RakNet::SocketDescriptor * sd;
	RakNet::SystemAddress host_addr;

	virtual void start_peer(RakNet::SystemAddress addr) {}
	virtual void send(WWEvent * e) {}


};


#endif