#include "Object_factory.h"

#include <zenilib.h>

#include "Collidable.h"
#include "Player.h"
#include "Team.h"

#include "Game_Model.h"

#include <vector>

using namespace Zeni;


Player *create_player(const Point3f &init)
{
	/*
	int lowest_area = 1;
	if (Game_Model::get().difficulty < 3)
		lowest_area = 3;	

	else if (Game_Model::get().difficulty == 3)
		lowest_area = 2;
	*/

//	if (type == "Player")
		return new Player(init);
	
//	else
//		throw Error("Trying to create object of unknown type!");
}

Team *create_team(Tile * Base_Tile)	{
	return new Team(Base_Tile);
}

/*
Game_Object *create_target(const String& type, const Point3f &init)
{
	int lowest_area = 1;

	if (type == "small")
		return new Target(init, 25, 20);
	if (type == "medium")
		return new Target(init, 50, 10);
	if (type == "large")
		return new Target(init, 100, 5);
	
	else
		throw Error("Trying to create object of unknown type!");
}
*/

/*
Game_Object *get_rand_target()
{
	Random r;
	
	int num_targets_c = 3;
	int map_size = 2000;

//	if (Game_Model::get().difficulty < 2 || Game_Model::get().difficulty == 4)
//		num_targets_c = 2;
	
	int z_start = 0;
	int z_large = map_size;
	
	z_start = map_size * (Game_Model::get().difficulty - 1);

	if (Game_Model::get().difficulty > 2)
		z_large = map_size*2;

	Point3f init(r.rand_lte(map_size)-map_size/2, r.rand_lte(map_size)-map_size/2, r.rand_lte(z_large)-z_start);

	switch (r.rand_lte(num_targets_c-1))
	{
		case 0:
			return create_target("small", init);
			break;

		case 1:
			return create_target("medium", init);
			break;

		case 2:
			return create_target("large", init);
			break;
	}
}
*/