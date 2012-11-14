#pragma once


#include <vector>
#include <set>
#include <map>

#include "Seen_Object.h"

class Player_View;
//class Seen_Object;

class View
{
public:
	View(void);
	~View(void);

	void render();

	void remove_renderable(Seen_Object *);
	void add_renderable(Seen_Object *);

private:
	std::vector<Player_View*> player_views;
	std::set<Seen_Object*> to_render;

	std::map<model_key_t, Zeni::Model*> model_map;

	void render_world() const;
	void render_renderable(const Seen_Object *to_rend) const;
};
