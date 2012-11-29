#pragma once
#include "Collidable.h"
#include "Seen_Object.h"

//These enums represnt the different types of buildings for now
//Will eventually be able to plug these into create_structure
//From object factory, hopefully anyway

enum Structure_Type	{
	NOTHING, SNOWMAN, FORT, SNOW_FACTORY, HEALING_POOL
};
//Nothing is used for when he player doesn't select a structure

//int structure_cost(Structure_Type B)	{
//	switch(B)	{
//	case SNOWMAN:
//		return 10;
//	case FORT:
//		return 20;
//	case SNOW_FACTORY:
//		return 30;
//	case HEALING_POOL:
//		return 40;
//	case NOTHING:
//	default:
//			return 0;
//			break;
//	}
//}


class Structure :
	public Collidable, public Seen_Object
{
public:
	Structure(void);
	~Structure(void);
};

