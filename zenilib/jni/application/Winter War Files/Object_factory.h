#ifndef SHIP_FACTORY_H
#define SHIP_FACTORY_H

#include <string>
#include <zenilib.h>

class Player;
class Team;
class Tile;

// not very useful now....
Player *create_player(const Zeni::Point3f &init_position);
Team	*create_team(Tile * Base_Tile);

//Collidable *create_target(const Zeni::String& type, const Zeni::Point3f &init_position);

//Collidable *get_rand_target();

#endif
