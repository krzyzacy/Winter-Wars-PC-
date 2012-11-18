#include "Game_Model.h"
#include "View.h"
#include "World.h"

Game_Model::Game_Model(void) :
	view(new View()), world(new World(view))
{
}


Game_Model::~Game_Model(void)
{
}
