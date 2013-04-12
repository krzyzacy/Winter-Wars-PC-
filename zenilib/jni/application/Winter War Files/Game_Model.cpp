#include "Game_Model.h"
#include "View.h"
#include "World.h"
#include "Object_factory.h"

#include "Player.h"
#include "Team.h"
#include "Player_View.h"
#include "Snowball.h"
#include "Structure.h"
#include "Effect.h"

#include "Tile.h"

#include <zenilib.h>
#include "Zeni/Joysticks.h"


using namespace std;
using namespace Zeni;


const float time_to_win_c = 20.0f; //max time it should take to win

Game_Model::Game_Model(void)
{

}

void Game_Model::start_up(const vector<String> &genders_, const vector<int> &colors_)
{
		view = (new View());
		world = (new World(view));
		time_passed = (0.0f); 
		time_step = (0.0f);	
		win_time = (10000.0f);

		breaking = new Zeni::Sound_Source(get_Sounds()["breaking"]);
		chainbreak = new Zeni::Sound_Source(get_Sounds()["chainbreak"]);
		presentplace = new Zeni::Sound_Source(get_Sounds()["presentplace"]);
		snowballthrow = new Zeni::Sound_Source(get_Sounds()["snowballthrow"]);
		bgm = new Zeni::Sound_Source(get_Sounds()["bgm"]);

		breaking->set_gain(0.35);
		breaking->set_pitch(0.8);

		chainbreak->set_gain(0.32);
		chainbreak->set_pitch(0.8);

		presentplace->set_gain(0.8);
		presentplace->set_pitch(0.8);

		snowballthrow->set_gain(0.8);
		snowballthrow->set_pitch(2);

		bgm->set_looping(1);


		teams.push_back(create_team(world->get_next_Base_Tile()));
		teams.push_back(create_team(world->get_next_Base_Tile()));
		teams.push_back(create_team(world->get_next_Base_Tile()));
		teams.push_back(create_team(world->get_next_Base_Tile()));
		teams[0]->set_Team_Color(GREEN);
		teams[1]->set_Team_Color(RED);
		teams[2]->set_Team_Color(BLUE);
		teams[3]->set_Team_Color(ORANGE);


	for(int i = 0; i < 4; i++){
		Player *p = create_player(teams[colors_[i]], genders_[i]);
		//Player *p = create_player(teams[i], genders_[i]);
		add_player(p);
	}

		// Place Tree
		add_structure(create_structure(TREE, world->get_center_Tile(), NULL));

		PlayTime.reset();
		PlayTime.start();
//		view->add_renderable(&Perm);

		play_bgm();
}

void Game_Model::restart()
{
	vector<String> genders;
	vector<int> colors;
	
	for(int i = 0; i < players.size(); i++){
		genders.push_back(String(players[i]->get_gender()));
		colors.push_back(players[i]->get_team()->get_Team_Index()-1);

	}
	
	finish();

	start_up(genders, colors);

}

void Game_Model::finish()
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
	
	//delete sounds
	delete breaking;
	delete chainbreak;
	delete presentplace;
	delete snowballthrow;

	PlayTime.reset();
}

Game_Model::~Game_Model(void)
{
//	finish();
}

void Game_Model::update()
{	
	const float frametime_passed = PlayTime.seconds();
	const float currentStep = frametime_passed - time_passed;
	time_passed = frametime_passed;
	time_step = currentStep;

	if (PlayTime.seconds() < 3 && PlayTime.seconds() > 2)
		global_message("Build a path of structures from your base to the Tree!");


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

	Game_Model::get().Clean_dead();
}

/*set the time to win and the team to win*/
void Game_Model::tree_claimed(const Team *team)
{
	// if no team owns the tree
	if (!team)
	{
		world->get_center_Tile()->set_team(NEUTRAL);
		win_time = 10000.0f;
		return ;
	}
	for (int i = 0; i < 4 ; i++)
	{
		if (get_team(i) != team)
		const_cast<Team*>(get_team(i))->message_team(const_cast<Team*>(team)->get_name_Upper_Case() + 
			" TEAM CLAIMED THE TREE! Destroy tiles to break their territory",80);
	}
	// team wants to own the tree
	win_time = PlayTime.seconds() + time_to_win_c;

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


// returns true if some team has won
bool Game_Model::win()
{
	if (time_till_win() <= 0)
	{
		for(int i = 0; i < 4; i++)
			Joysticks::get().set_xinput_vibration(i, 0, 0);

		PlayTime.stop();
		return true;
	}
	return false;
}

/* return time game has been played*/
float Game_Model::get_time() const
{
	return PlayTime.seconds();
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

void Game_Model::add_effect(Effect* S)	{
	effects.insert(S);
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


void Game_Model::remove_from_model(Moveable* Z)	{
	movers.erase(Z);
	colliders.erase(Z);
	view->remove_renderable(Z);
	delete Z;
}

void Game_Model::remove_from_model(Effect* Z)	{
	effects.erase(Z);
	view->remove_renderable(Z);
	delete Z;
}

void Game_Model::remove_from_model(Structure* Z)	{
	colliders.erase(Z);
	structures.erase(Z);
	view->remove_renderable(Z);
	delete Z;
}

float Game_Model::time_till_win() const
{
	return win_time - PlayTime.seconds();
}

void Game_Model::global_message(const String &message)
{	
	for(int i = 0; i < 4; i++)
	{
		players[i]->add_message(message);
	}
}

void Game_Model::play_breaking()
{
	if(!breaking->is_playing())
		breaking->play();
}

void Game_Model::play_chainbreak()
{
	if(!chainbreak->is_playing())
		chainbreak->play();
}

void Game_Model::play_presentplace()
{
	presentplace->play();
}

void Game_Model::play_snowballthrow()
{
	snowballthrow->play();
}

void Game_Model::play_bgm(){
	if(!bgm->is_playing())
		bgm->play();
}

void Game_Model::stop_bgm(){
	if(bgm->is_playing())
		bgm->stop();
}

Tile *Game_Model::get_tile(const Point3f& pos)
{
	return world->get_tile(pos);
}