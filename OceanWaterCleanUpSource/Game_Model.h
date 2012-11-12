#pragma once

#include <vector>
#include <zenilib.h>

#include "Collision_Table.h"
#include "World.h"

class Game_Object;
class Player;

class Game_Model
{
public:
	static Game_Model &get()
	{
		static Game_Model m;
		return m;
	}

	~Game_Model(void);

	void update();
	
	void render() const;
	Player *get_player(int num) const;

	float time_step()
		{return m_time_step;}

	bool game_over();
	void restart(int players, int diff);

	void finish_game();

	int get_score() const;

	bool win(){ return false;}

	void stop();

	void add_obj(Game_Object *go);
	
	float get_time_left();

	int get_z(int x, int y) {
		return world.get_z(x,y);
	}

	void add_to_delete(Game_Object *go);

	int num_players;
	int difficulty;

private:
	bool finished;
	Zeni::Light m_light;

	std::vector<Game_Object*> objs;
	std::vector<Player*> players;
	std::vector<Game_Object*> to_delete;

	Zeni::Chronometer<Zeni::Time> m_chrono;
	float m_time_passed;
	float m_time_step;
	float time_started;

	World world;


	float cur_time() const
		{return m_time_passed - time_started;}
	
	void start(int players);
	void remove_ob(Game_Object *ob);

	void check_collisions();
	bool is_colliding(Game_Object *ob1, Game_Object *ob2);

	Collision_Table table;

	Game_Model();
	Game_Model(const Game_Model &);
	Game_Model &operator=(const Game_Model &);
 };

