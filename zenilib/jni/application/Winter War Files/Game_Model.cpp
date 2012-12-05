#include "Game_Model.h"
#include "View.h"
#include "World.h"
#include "Object_factory.h"

#include "Player.h"
#include "Team.h"
#include "Player_View.h"
#include "Snowball.h"
#include "Structure.h"

#include "Tile.h"

#include <zenilib.h>

using namespace std;
using namespace Zeni;



Game_Model::Game_Model(void)
{

}

void Game_Model::start_up(const std::vector<String> &genders_, const std::vector<int> &colors_)
{
		view = (new View());
		world = (new World(view));
		time_passed = (0.0f); 
		time_step = (0.0f);	
		

		teams.push_back(create_team(world->get_next_Base_Tile()));
		teams.push_back(create_team(world->get_next_Base_Tile()));
		teams.push_back(create_team(world->get_next_Base_Tile()));
		teams.push_back(create_team(world->get_next_Base_Tile()));
		teams[0]->set_Team_Color(GREEN);
		teams[1]->set_Team_Color(RED);
		teams[2]->set_Team_Color(BLUE);
		teams[3]->set_Team_Color(ORANGE);


	for(int i = 0; i < 4; i++){
		Player *p = create_player(teams[colors_[i]], "Girl");//genders_[i]);
		//Player *p = create_player(teams[i], "Girl");
		add_player(p);
	}

		// Place Tree
		add_structure(create_structure(TREE, world->get_center_Tile(), NULL));

		PlayTime.reset();
		PlayTime.start();
//		view->add_renderable(&Perm);

}



void Game_Model::finish()
{
	//Everything is a collidable in all the other lists, so this represents all things
	for(collidable_list_t::iterator it = colliders.begin(); it != colliders.end(); ++it)
		delete (*it);

	delete world; //destroys tiles too
	delete view;	

	movers.clear();
	colliders.clear();
	structures.clear();

	// if we want to cfreate players and teams outside of this
	// cant clear players and team too
	players.clear();

	for(vector<Team*>::iterator it = teams.begin(); it != teams.end(); ++it)	
		delete (*it);
	teams.clear();
	
	PlayTime.reset();
}

Game_Model::~Game_Model(void)
{
	finish();
}

void Game_Model::update()
{	
	const float frametime_passed = PlayTime.seconds();
	const float currentStep = frametime_passed - time_passed;
	time_passed = frametime_passed;
	time_step = currentStep;


	for(collidable_list_t::iterator it = colliders.begin(); it != colliders.end(); it++)
		(*it)->update(time_step);

	for(vector<Team*>::iterator it = teams.begin(); it != teams.end(); ++it)
		(*it)->update();


	for(vector<Team*>::iterator it = teams.begin(); it != teams.end(); ++it)	{
		if((*it)->Is_Tree_Claimed())
			world->raise_tile(world->get_center_Tile()->get_structure_base());
		//get_Game().pop_state(); Do something to win
	}

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

float Game_Model::get_time_step()	{
	return time_step;
}

void Game_Model::add_player(Player *p)
{
	players.push_back(p);
	view->add_renderable(p);
	view->add_player_view(new Player_View(p));
	colliders.insert(p);
	movers.insert(p);
}

void Game_Model::add_moveable(Moveable *m)
{
	movers.insert(m);
	colliders.insert(m);
	view->add_renderable(m);
}

void Game_Model::add_structure(Structure* S)	{
	colliders.insert(S);
	structures.insert(S);
	view->add_renderable(S);
}


void Game_Model::Clean_dead()	{
		// Runs through destructable objects to check if they have died
		//places them in trash list if they have
		for(moveable_list_t::iterator it = movers.begin(); it != movers.end(); ++it)	{
			if(!(*it)->is_alive())
				m_deletion_list.push_back(*it);
		}

		for(set<Structure*>::iterator it = structures.begin(); it != structures.end(); ++it)		{
			if(!(*it)->is_alive())
				s_deletion_list.push_back(*it);
		}
		//one more loop for visual effects, if neccessary

		//Clean trash
		for(list<Moveable*>::iterator it = m_deletion_list.begin(); it != m_deletion_list.end(); ++it)	
				remove_from_model(*it);

		for(list<Structure*>::iterator it = s_deletion_list.begin(); it != s_deletion_list.end(); ++it)		
				remove_from_model(*it);
		
		m_deletion_list.clear();
		s_deletion_list.clear();
}


void Game_Model::remove_from_model(Moveable* Z)	{
	movers.erase(Z);
	colliders.erase(Z);
	view->remove_renderable(Z);
	delete Z;
}

void Game_Model::remove_from_model(Structure* Z)	{
	colliders.erase(Z);
	structures.erase(Z);
	view->remove_renderable(Z);
	delete Z;
}


