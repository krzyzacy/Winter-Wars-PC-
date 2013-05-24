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

#define NUM_STRUCTURES 7

enum Structure_Type	{
	NOTHING, SNOWMAN, FORT, SNOW_FACTORY, HEALING_POOL, TREE, BASE
};



extern Zeni::String Structure_Names[NUM_STRUCTURES];

//Render scaled text
void scaled_render_text(const Zeni::String text, const Zeni::Point3f &position, const Zeni::Color &color, float range);

//Render scaled text, scaled by height
void scaled_render_text_height(const Zeni::String text, const Zeni::Point3f &position, const Zeni::Color &color, float height);

//Makes a time string of a XX:XX format
Zeni::String make_time_string(int seconds);