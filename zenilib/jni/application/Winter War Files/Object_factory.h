#ifndef SHIP_FACTORY_H
#define SHIP_FACTORY_H

#include <string>
#include <zenilib.h>
#include "Utility.h"

class Player;
class Team;
class Tile;
class Structure;

// gender can be "Boy" or "Girl"
Player *create_player(Team* team_, const Zeni::String &gender);

Player *create_player(Team* team_, const Zeni::String &gender, Tile *tile);

Team	*create_team(Tile * Base_Tile, TEAM_INDEX);

// creates a structure and adds it to the tile
Structure *create_structure(int type, Tile* ti, Team* team_);

#endif
