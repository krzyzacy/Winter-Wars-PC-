#include "Level.h"
#include "View.h"
#include "World.h"
#include "Object_factory.h"

#include "Player.h"
#include "Team.h"
#include "Player_View.h"
#include "Snowball.h"
#include "Structure.h"
#include "Effect.h"
#include "Controls.h"

#include "Tile.h"

#include <zenilib.h>
#include "Zeni/Joysticks.h"
#include "WWClient.h"


using namespace std;
using namespace Zeni;


const float time_to_win_c = 20.0f; //max time it should take to win


Level::Level()
{}

Level::~Level(void)
{
	finish();
}

void Level::start_up(const vector<Player_info*> &player_info)
{
	init_player_info = player_info;

	view = (new View());
	world = (new World(view));
	time_passed = (0.0f); 
	time_step = (0.0f);	
	win_time = (10000.0f);


	teams.push_back(create_team(world->get_next_Base_Tile()));
	teams.push_back(create_team(world->get_next_Base_Tile()));
	teams.push_back(create_team(world->get_next_Base_Tile()));
	teams.push_back(create_team(world->get_next_Base_Tile()));
	teams[0]->set_Team_Color(GREEN);
	teams[1]->set_Team_Color(RED);
	teams[2]->set_Team_Color(BLUE);
	teams[3]->set_Team_Color(ORANGE);


	for(int i = 0; i < player_info.size() ; i++){
		Player *p = create_player(teams[player_info[i]->colors_], player_info[i]->genders_);
		//Player *p = create_player(teams[i], genders_[i]);
		add_player(p);
	}

	// Place Tree
	add_structure(create_structure(TREE, world->get_center_Tile(), NULL));

	PlayTime.reset();
	PlayTime.start();

	if (!WWClient::isNetwork())
		// not a network game
	{	// put all players in views
		for ( int i = 0 ; i < num_players() ; i++)
			view->add_player_view(new Player_View(get_player(i)));
	}
}

void Level::initialize_peer(bool isServer, RakNet::SystemAddress host_addr){

	if(isServer){
		peer = new Ingame_Server();
	}

	if (WWClient::isNetwork())	
	{
		WWClient::get()->setHostAddr(host_addr);	

		cerr << WWClient::get()->get_my_address().ToString();

		// set up map of players
		for (int i = 0 ; i < init_player_info.size() ; i++)
		{
			// insert this player into the map at his client's address
			clients_to_players[init_player_info.at(i)->self_addr].push_back(get_player(i));
			
			// only players on this machine get a view.
			if (init_player_info.at(i)->self_addr != RakNet::UNASSIGNED_SYSTEM_ADDRESS && 
				init_player_info.at(i)->self_addr.GetPort() == WWClient::get()->get_my_address().GetPort())
			{
				view->add_player_view(new Player_View(get_player(i)));
			}

		}
	}
}

void Level::restart()
{
	finish();

	start_up(init_player_info);
}

void Level::finish()
{
	//Everything is a collidable in all the other lists, so this represents all things
	for(collidable_list_t::iterator it = colliders.begin(); it != colliders.end(); ++it)
		delete (*it);
	
	for(set<Effect*>::iterator it = effects.begin(); it != effects.end(); ++it)
		delete (*it);

	delete world; //destroys tiles too
	delete view;	

	movers.clear();
	colliders.clear();
	structures.clear();
	effects.clear();

	// if we want to cfreate players and teams outside of this
	// cant clear players and team too
	players.clear();

	for(vector<Team*>::iterator it = teams.begin(); it != teams.end(); ++it)	
		delete (*it);
	teams.clear();
	

	PlayTime.reset();
}



void Level::update()
{	
	const float frametime_passed = PlayTime.seconds();
	const float currentStep = frametime_passed - time_passed;
	time_passed = frametime_passed;
	time_step = currentStep;

	//if (PlayTime.seconds() < 3 && PlayTime.seconds() > 2)
	//{
	//	global_message("Build a path of structures from your base to the Tree!");
	//}

	for(collidable_list_t::iterator it = colliders.begin(); it != colliders.end(); it++)
		(*it)->update(time_step);

	for(vector<Team*>::iterator it = teams.begin(); it != teams.end(); ++it)
		(*it)->update();


	for(vector<Team*>::iterator it = teams.begin(); it != teams.end(); ++it)	{
		if((*it)->Is_Tree_Claimed())
		{
			world->raise_tile(world->get_center_Tile()->get_structure_base());
		}	
	}
	
	check_collisions();

	Clean_dead();


	view->animate();
}



/*set the time to win and the team to win*/
void Level::tree_claimed(const Team *team)
{
	// if no team owns the tree
	if (!team)
	{
		world->get_center_Tile()->set_team(NEUTRAL);
		win_time = 10000.0f;
		return ;
	}
	for (int i = 0; i < num_players() ; i++)
	{
		if (get_team(i) != team)
		const_cast<Team*>(get_team(i))->message_team(const_cast<Team*>(team)->get_name_Upper_Case() + 
			" TEAM CLAIMED THE TREE! Destroy tiles to break their territory",80);
	}
	// team wants to own the tree
	win_time = PlayTime.seconds() + time_to_win_c;

}


void Level::check_collisions()
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


// returns true if some team has won
bool Level::win()
{
	if (time_till_win() <= 0)
	{
		PlayTime.stop();
		return true;
	}
	return false;
}

/* return time game has been played*/
float Level::get_time() const
{
	return PlayTime.seconds();
}

void Level::render() const
{
	view->render();
}

float Level::get_time_step()	{
	return time_step;
}

void Level::add_player(Player *p)
{
	players.push_back(p);
	view->add_renderable(p);	
	colliders.insert(p);
	movers.insert(p);
}

void Level::add_moveable(Moveable *m)
{
	movers.insert(m);
	colliders.insert(m);
	view->add_renderable(m);
}

void Level::add_structure(Structure* S)	{
	colliders.insert(S);
	structures.insert(S);
	view->add_renderable(S);
}

void Level::add_effect(Effect* S)	{
	effects.insert(S);
	view->add_renderable(S);
}

void Level::Clean_dead()	{
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

		for(set<Effect*>::iterator it = effects.begin(); it != effects.end(); ++it)		{
			if(!(*it)->is_alive())
				e_deletion_list.push_back(*it);
		}

		//Clean trash
		for(list<Moveable*>::iterator it = m_deletion_list.begin(); it != m_deletion_list.end(); ++it)	
				remove_from_model(*it);

		for(list<Structure*>::iterator it = s_deletion_list.begin(); it != s_deletion_list.end(); ++it)		
				remove_from_model(*it);

		for(list<Effect*>::iterator it = e_deletion_list.begin(); it != e_deletion_list.end(); ++it)	
				remove_from_model(*it);

		
		m_deletion_list.clear();
		s_deletion_list.clear();
		e_deletion_list.clear();
}

float Level::time_till_win() const
{
	return win_time - PlayTime.seconds();
}

void Level::global_message(const String &message)
{	
	for(int i = 0; i < 4; i++)
	{
		players[i]->add_message(message);
	}
}

Tile *Level::get_tile(const Point3f& pos)
{
	return world->get_tile(pos);
}

void Level::remove_from_model(Moveable* Z)	{
	movers.erase(Z);
	colliders.erase(Z);
	view->remove_renderable(Z);
	delete Z;
}

void Level::remove_from_model(Effect* Z)	{
	effects.erase(Z);
	view->remove_renderable(Z);
	delete Z;
}

void Level::remove_from_model(Structure* Z)	{
	colliders.erase(Z);
	structures.erase(Z);
	view->remove_renderable(Z);
	delete Z;
}

Player *Level::get_player_here(int i)
{
	if (WWClient::isNetwork())
		return clients_to_players[WWClient::get()->get_my_address()].at(i);

	//if it is local
	return get_player(i);
}

int Level::num_players_here()
{	
	if (WWClient::isNetwork())
		return clients_to_players[WWClient::get()->get_my_address()].size();

	//if it is local
	return num_players();
}