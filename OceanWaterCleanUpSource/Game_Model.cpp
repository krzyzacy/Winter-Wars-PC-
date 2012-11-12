#include "Game_Model.h"

#include "Game_Object.h"
#include "Player.h"
#include "Object_factory.h"
#include "zenilib.h"
#include "Utility.h"
#include "high_scores.h"

#include "World.h"

#include <zeni/Sound_Buffer.h>
#include <vector>
#include <fstream>

using namespace Zeni;
using namespace std;

const int game_length_c = 60;


static int high_score;
static int low_score;
const int scores_saved_c = 8;


Game_Model::Game_Model(void) : 
		objs()
		, players()
		, to_delete()
		, finished(false)
{

}

void set_light(Light &m_light)
{
    m_light.ambient = Color(1.0f,.5,.5,.5);
    m_light.diffuse = Color(1.0f,.5,.5,.5);
    m_light.specular = Color(1.0f,.5,.5,.5);

    m_light.position = Point3f(100,100,100);
}

void Game_Model::restart(int num, int diff)
{
	for (int i = 0 ; i < objs.size() ; i++)
	{
		delete objs[i];
	}
	objs.clear();
	players.clear();
//	statics.clear();
//	static_texts.clear();
	
	difficulty = diff;

	start(num);
}

void Game_Model::start(int num_players_)
{
	int max_ball_c = difficulty * 3;


	num_players = num_players_;

	Player *p;
	objs.push_back(p = dynamic_cast<Player*>(create_ob("Player",
		Point2f(0,0))));

	players.push_back(p);

	if (num_players > 1)
	{
		objs.push_back(p = dynamic_cast<Player*>(create_ob("Player",
			Point2f(10,10))));
		players.push_back(p);
	}

	m_chrono.start();
	time_started = m_chrono.seconds();
	
	for (int i = 0 ; i < 100*difficulty ; i++) 
	//	objs.push_back(create_target("Target", Vector3f(i*100,i*100,100)));
		objs.push_back(get_rand_target());

/*
	multiset<Score_t> scores;
	get_HS(scores,("hs" + itoa(difficulty + 100*num_players) + ".txt").data());
	
	if (scores.size() > 1)
		low_score = *scores.begin();	
	if (scores.size() > 0)	
		high_score = *scores.rbegin();
*/

	finished = false;
	set_light(m_light);
}

Game_Model::~Game_Model(void)
{
}



void Game_Model::update()
{		
	if (game_over())
		return;

/*
	for (int i = 0 ;  i < statics.size() ; i++)
		statics[i].time-- ;
			
	for (int i = 0 ;  i < static_texts.size() ; i++)
		static_texts[i].time-- ;
 */	

	for_each(objs.begin(), objs.end(), mem_fun(&Game_Object::update));

	check_collisions();


	for_each(to_delete.begin(), to_delete.end(), bind1st(mem_fun(&Game_Model::remove_ob),this));
	to_delete.clear();

	float time_passed = 0;
	m_time_step = 0;

	while (m_time_step < 1.0f/frame_rate_c)
	{	
		time_passed = m_chrono.seconds();	
		m_time_step = time_passed - m_time_passed;
	}
	m_time_passed = time_passed;

}

float Game_Model::get_time_left()
{return (game_length_c - cur_time());
}

bool Game_Model::game_over()
{
	if (get_time_left() < 0)
		return true;

	return false;
}

Player *Game_Model::get_player(int num) const
{
	return players.at(num);
}

void Game_Model::render() const
{   
    Video &vr = get_Video();

//	vr.set_lighting(true);
    vr.set_ambient_lighting(Color(1.0f, 0.0f, 0.0f, 0.0f));
    vr.set_Light(0, m_light);
	world.render();

	for_each(objs.begin(), objs.end()
		, mem_fun(&Game_Object::render));
	
	int y_incr = 50;

/*
	for (int i = 0 ;  i < statics.size() ; i++)
		if (statics[i].time > 0)
			render_image(
			  "static_1", // which texture to use
			  statics[i].pos, // upper-left corner
			  statics[i].pos + Point2f(64,64), ZENI_CENTER);

	
	for (int i = 0 ;  i < static_texts.size() ; i++)
		if (static_texts[i].time > 0)
		{ 
			get_Fonts()[static_texts[i].size].render_text(
				static_texts[i].msg
			, static_texts[i].pos, static_texts[i].col, ZENI_CENTER);
		}

*/

	
    vr.set_lighting(false);
}

void Game_Model::check_collisions()
{
	for (size_t i = 0 ; i < objs.size() ; i++)
		for (size_t j = i+1 ; j < objs.size() ; j++)
		{
			if (objs[i]->get_body().intersects(objs[j]->get_body()))
				table.handle_collision(objs[i]->get_ID()
					, objs[j]->get_ID(), objs[i], objs[j]);
		}
}

void Game_Model::remove_ob(Game_Object *ob)
{
	objs.erase(find(objs.begin(), objs.end(), ob));
	delete ob;	
}

int Game_Model::get_score() const
{
	int score = 0;
	for (int i = 0 ; i < players.size() ; i++)
		score += players[i]->get_score();

	return score;
}


void Game_Model::finish_game()
{
	if (finished)
		return;
	//*
	multiset<Score_t> scores;

	get_HS(scores, ("hs" + itoa(difficulty + 100*num_players) + ".txt").data());

	if (scores.empty())
	{}
	// if the score is less than the lowest score
	else if (get_score()< *scores.begin() && scores.size() >= 8)
		return;

	if (scores.size() > scores_saved_c)
		scores.erase(scores.begin());

	scores.insert(get_score());

	ofstream fout(("hs" + itoa(difficulty + 100*num_players) + ".txt").data());
	
	save_HS(scores, fout);

	fout.close();

	finished = true;
	//*/
}


void Game_Model::add_obj(Game_Object *go)
{
	objs.push_back(go);
}


void Game_Model::add_to_delete(Game_Object *go)
{
	if (find(to_delete.begin(), to_delete.end(), go) !=  to_delete.end())
		return; // it's already been popped

	to_delete.push_back(go);	
}
