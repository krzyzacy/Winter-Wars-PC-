#include "World.h"

#include <vector>
#include <zenilib.h>

using namespace Zeni;
using namespace std;
using namespace Zeni::Collision;

World::World(void) :
	map(100, vector<Tile>(100, Tile()))
	, model(new Model("models/world3.3ds"))
{
	
}

World::~World(void)
{


}

void World::render() const 
{

//    get_m()->set_translate(center());
    model->set_scale(Vector3f(200,200,200));
	model->render();
}

int World::get_z(int x, int y) 
{
	return 0;







	if (x > map.size() || y > map.at(0).size())
		return 1000000000;

	return map.at(x).at(y).height;
}