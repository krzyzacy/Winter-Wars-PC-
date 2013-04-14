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

	Ingame_Peer();
	~Ingame_Peer();


	RakNet::RakPeerInterface peer;
	virtual void initialize(bool isServer);
	virtual void send(Event * e);
	virtual void 

};


#endif