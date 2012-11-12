#ifndef SHIP_FACTORY_H
#define SHIP_FACTORY_H

#include <string>
#include <zenilib.h>

class Game_Object;

Game_Object *create_ob(const Zeni::String& type, const Zeni::Point2f &init_position);
Game_Object *create_target(const Zeni::String& type, const Zeni::Point3f &init_position);

Game_Object *get_rand_target();

#endif
