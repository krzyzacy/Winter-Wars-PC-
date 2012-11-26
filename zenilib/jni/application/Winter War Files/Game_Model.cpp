#include "Game_Model.h"
#include "View.h"
#include "World.h"
#include "Object_factory.h"

#include "Player.h"
#include "Player_View.h"
#include "Snowball.h"

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
			,Point3f(100,300,100) ,Point3f(500,100,50), Point3f(100,100,20)};

		for (int i = 0 ; i < 4 ; i++)
		{
			Player *p = create_player(p_points[i]);
			players.push_back(p);
			view->add_renderable(p);
			view->add_player_view(new Player_View(p));
			colliders.insert(p);
			movers.insert(p);
		}
		
//		view->add_renderable(&Perm);

}

Game_Model::~Game_Model(void)
{
	delete world;
	delete view;
}

void Game_Model::update(const float &time)
{	
	for(collidable_list_t::iterator it = colliders.begin(); it != colliders.end(); ++it)
		(*it)->update(time);

	//get_player(0)->throw_ball();

	check_collisions();
}

void Game_Model::check_collisions()
{
	// for each moveable/collidable pair
	for(moveable_list_t::iterator it = movers.begin()
						; it != movers.end(); ++it)
		for(collidable_list_t::iterator jt = colliders.begin()
							; jt != colliders.end(); ++jt)
		{
			table.handle_collision((*it)->get_ID(), (*jt)->get_ID()
				, *it, *jt);
		}
}

void Game_Model::render() const
{
	view->render();
}

void Game_Model::add_moveable(Moveable *m)
{
	movers.insert(m);
	colliders.insert(m);
	view->add_renderable(m);
}

void Game_Model::remove_moveable(Moveable *m)	{
		movers.erase(m);
		colliders.erase(m);
		view->remove_renderable(m);
		delete m;
}

void Game_Model::Clean_Moving_dead()	{
	list<Moveable*> Trash;
	for(moveable_list_t::iterator it = movers.begin(); it != movers.end(); ++it)	{
		if(!(*it)->is_alive())
			Trash.push_back(*it);
	}

	for(list<Moveable*>::iterator it = Trash.begin(); it != Trash.end(); ++it)	
		remove_moveable(*it);
}


