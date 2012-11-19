#include "Game_Model.h"
#include "View.h"
#include "World.h"
#include "Object_factory.h"

#include "Player.h";
#include "Player_View.h"

#include <zenilib.h>

using namespace Zeni;

// REMOVE THESE LATER
#include "Permanent.h"



Game_Model::Game_Model(void) :
	view(new View()), world(new World(view))
		, Perm(new Permanent(Point3f(30,10,0), Vector3f(2,2,2)))

{
	start_up();
}

void Game_Model::start_up()
{

		Point3f p_points[] = {Point3f(1,0,20)
			,Point3f(10,30,100) ,Point3f(0,0,50), Point3f(10,10,20)};

		for (int i = 0 ; i < 4 ; i++)
		{
			Player *p = create_player(p_points[i]);
			players.push_back(p);
			view->add_renderable(p);
			view->add_player_view(new Player_View(p));
		}
		
//		view->add_renderable(&Perm);

}

Game_Model::~Game_Model(void)
{
	delete world;
	delete view;
}

void Game_Model::update()
{	


}

void Game_Model::render() const
{
	view->render();
}