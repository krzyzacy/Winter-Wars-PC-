#ifndef SHIP_FACTORY_H
#define SHIP_FACTORY_H

#include <string>
#include <zenilib.h>

class Player;
class Team;
class Tile;
class Structure;


// not very useful now....
Player *create_player(const Zeni::Point3f &init_position);
Team	*create_team(Tile * Base_Tile);

// Figure out tile and team from player!!
Structure *create_structure(const std::string &type, Player *player, const Zeni::Point3f &init_position);


#endif
