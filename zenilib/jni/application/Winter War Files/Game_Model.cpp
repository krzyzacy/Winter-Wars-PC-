#include "Game_Model.h"
#include "View.h"
#include "World.h"
#include "Object_factory.h"

#include "Player.h"
#include "Team.h"
#include "Player_View.h"
#include "Snowball.h"

#include <zenilib.h>

using namespace std;
using namespace Zeni;



Game_Model::Game_Model(void) :
	view(new View()), world(new World(view)), time_passed(0.0f), time_step(0.0f)
{
	start_up();
}

void Game_Model::start_up()
{
		Point3f p_points[] = { Point3f(100, 100, 10), Point3f(100, 500,10) ,Point3f(500, 500, 10), Point3f( 500, 100, 10)};

		//&&& This is the team set up, for now it's hard coded to 2, 
		//but when we add the menu, should be easy to extend for up to 4 teams
		teams.push_back(create_team(world->get_next_Base_Tile()));
		teams.push_back(create_team(world->get_next_Base_Tile()));


		for (int i = 0 ; i < 4 ; i++)
		{
			Player *p = create_player(p_points[i]);
			players.push_back(p);
			view->add_renderable(p);
			view->add_player_view(new Player_View(p));
			colliders.insert(p);
			movers.insert(p);
			//This will also change based on the menu set up
			if(i <= 1)	{
				teams[0]->add_player(p);
				p->set_Team(teams[0]);
			}
			else	{
				teams[1]->add_player(p);
				p->set_Team(teams[1]);
			}
		}
		
		PlayTime.start();
//		view->add_renderable(&Perm);

}

Game_Model::~Game_Model(void)
{
	//Everything is a collidable in all the other lists, so this represents all things
	//besides seen objects, which hopefully no overlap??? View must destroy those
	for(collidable_list_t::iterator it = colliders.begin(); it != colliders.end(); ++it)
		delete (*it);

	for(vector<Team*>::iterator it = teams.begin(); it != teams.end(); ++it)	
		delete (*it);

	delete world;
	delete view;
}

void Game_Model::update()
{	
	const float frametime_passed = PlayTime.seconds();
	const float currentStep = frametime_passed - time_passed;
	time_passed = frametime_passed;
	time_step = currentStep;



	for(collidable_list_t::iterator it = colliders.begin(); it != colliders.end(); ++it)
		(*it)->update(time_step);

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

float Game_Model::get_time_step()	{
	return time_step;
}

void Game_Model::Kill_me(Moveable *Deadman)	{
		movers.erase(Deadman);
		colliders.erase(Deadman);
		view->remove_renderable(Deadman);
		delete Deadman;
}

