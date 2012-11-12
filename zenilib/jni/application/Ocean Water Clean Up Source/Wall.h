#pragma once

#include "game_object.h"

class Wall :
	public Game_Object
{
public:
	Wall(Zeni::Point2f pos, Zeni::Vector2f size) : 
	  Game_Object(pos, size, 1000000000)
	  {}

	  ~Wall(){}

	  void render() const
	  { }
	  
	  void update() {}
	
	  int get_ID() const
		{return wall_ID_c;}
	  int get_parent_ID() const
		{return Game_Object::get_ID();}

private:	
	const static int wall_ID_c;


	friend Collision_Table;
};

