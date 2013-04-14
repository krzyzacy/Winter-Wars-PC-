#pragma once

/*
	use for global structs and constants
*/

#include <zenilib.h>

#define MAX_CLIENTS 10
#define SERVER_PORT 60000
#define ROOM_CAPACITY 16

struct Player_info{
	int colors_;
	Zeni::String genders_;
	int controls_;
	int sensitivities_;
};

