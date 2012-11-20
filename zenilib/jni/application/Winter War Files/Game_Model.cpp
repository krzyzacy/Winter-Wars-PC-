#include "Game_Model.h"
#include "View.h"
#include "World.h"
#include "Object_factory.h"

#include "Player.h";
#include "Player_View.h"

#include <zenilib.h>

using namespace std;
using namespace Zeni;



Game_Model::Game_Model(void) :
	view(new View()), world(new World(view))
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
			colliders.push_back(p);
			movers.push_back(p);
		}
		
//		view->add_renderable(&Perm);

}

Game_Model::~Game_Model(void)
{
	delete world;
	delete view;
}

void Game_Model::update(const float time)
{	
	for(vector<Moveable*>::iterator it = movers.begin(); it != movers.end(); ++it)
		(*it)->update(time);

	check_collisions();
}

void Game_Model::check_collisions()
{
	for (size_t i = 0 ; i < movers.size() ; i++)
		for (size_t j = 0 ; j < colliders.size() ; j++)
		{
			table.handle_collision(movers[i]->get_ID()
				, colliders[j]->get_ID(), movers[i], colliders[j]);
		}
}

void Game_Model::render() const
{
	view->render();
}