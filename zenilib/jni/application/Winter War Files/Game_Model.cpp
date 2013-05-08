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
#include "Controls.h"

#include "Tile.h"

#include <zenilib.h>
#include "Zeni/Joysticks.h"
#include "WWClient.h"

#include "Level.h"

using namespace std;
using namespace Zeni;

Game_Model::Game_Model(void)
{

}

void Game_Model::change_level(Level *new_level)
{
//	delete current_level;

	current_level = new_level;
}

void Game_Model::start_up(const vector<Player_info*> &player_info)
{
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

	play_bgm();

	current_level->start_up(player_info);
}

void Game_Model::initialize_peer(bool isServer, RakNet::SystemAddress host_addr){

	current_level->initialize_peer(isServer, host_addr);
}

void Game_Model::restart()
{
	current_level->restart();
}

void Game_Model::finish()
{
	delete current_level;

	//delete sounds
	delete breaking;
	delete chainbreak;
	delete presentplace;
	delete snowballthrow;
}

Game_Model::~Game_Model(void)
{

}

void Game_Model::update()
{	
	current_level->update();
}

/*set the time to win and the team to win*/
void Game_Model::tree_claimed(const Team *team)
{
	current_level->tree_claimed(team);
}

// returns true if some team has won
bool Game_Model::win()
{
	return current_level->win();
}

Team* Game_Model::get_winning_team()
{
	return current_level->get_winning_team();
}

/* return time game has been played*/
float Game_Model::get_time() const
{
	return current_level->get_time();
}

void Game_Model::render() const
{
	current_level->render();
}

float Game_Model::get_time_step()	
{
	return current_level->get_time_step();
}

void Game_Model::add_player(Player*p)
{
	current_level->add_player(p);
}

void Game_Model::add_moveable(Moveable *m)
{
	current_level->add_moveable(m);
}

void Game_Model::add_structure(Structure* S)	
{
	current_level->add_structure(S);
}

void Game_Model::add_effect(Effect* S)	
{
	current_level->add_effect(S);
}

float Game_Model::time_till_win() const
{
	return current_level->time_till_win();
}

void Game_Model::global_message(const String &message)
{	
	current_level->global_message(message);
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
	return current_level->get_tile(pos);
}

Tile *Game_Model::get_tile(int row, int col)
{
	return current_level->get_World()->get_tile(row, col);
}

Team *Game_Model::get_team(int i)
{
	return current_level->get_team(i);
}

World* Game_Model::get_World()
{
	return current_level->get_World();
}

Ingame_Server * Game_Model::get_peer()
{
	return current_level->get_peer();
}

Player *Game_Model::get_player(int i)
{
	return current_level->get_player(i);
}

Player *Game_Model::get_player_here(int i)
{
	return current_level->get_player_here(i);
}

int Game_Model::num_players()
{
	return current_level->num_players();
}
	
int Game_Model::num_players_here()
{
	return current_level->num_players_here();
}