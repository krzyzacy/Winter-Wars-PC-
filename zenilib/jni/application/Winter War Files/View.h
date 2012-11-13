#pragma once



#include <vector>
#include <set>
#include <map>

class Player_View;
class Renderable;


class View
{
public:
	View(void);
	~View(void);


	void render();

	void remove_renderable(Renderable *);
	void add_renderable(Renderable *);

private:
	std::vector<Player_View*> player_views;
	std::set<Renderable*> to_render;

	std::map<model_key_t, Zeni::Model*> model_map;

	void render_world() const;
	void render_renderable(const Renderable *to_rend) const;
};

