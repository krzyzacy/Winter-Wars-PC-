#pragma once



#include <vector>
#include <set>

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
};

