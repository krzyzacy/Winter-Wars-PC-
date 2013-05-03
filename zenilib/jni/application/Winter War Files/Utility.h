#pragma once

/*
	use for global structs and constants
*/

#include <zenilib.h>

#include "RakPeerInterface.h"

#define MAX_CLIENTS 10
#define SERVER_PORT 60000
#define ROOM_CAPACITY 16
#define MAX_PLAYER_NUM 4

#define HOST_PORT 61111

struct Player_info{
	int colors_;
	Zeni::String genders_;
	int controls_;
	int sensitivities_;
	RakNet::SystemAddress self_addr;
};

enum TEAM_INDEX	{
	NEUTRAL, GREEN, RED, BLUE, ORANGE
};

