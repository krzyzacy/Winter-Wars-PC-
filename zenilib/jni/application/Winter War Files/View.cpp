#include "View.h"

#include "Seen_Object.h"
#include "Player_View.h"

#include <functional>
#include <zenilib.h>

using namespace Zeni;

using namespace std;

View::View(void)
{
	model_map["snowball"] = new Zeni::Model("models/snowball.3ds");
	model_map["simpletile"] = new Zeni::Model("models/simpletile.3ds");
	model_map["world"] = new Zeni::Model("models/world2.3ds");
	model_map["player"] = new Zeni::Model("models/soap.3ds");

}

View::~View(void)
{
}

void View::add_renderable(Seen_Object *to_rend)
{
	to_render.insert(to_rend);
}

void View::remove_renderable(Seen_Object *to_rend)
{
	to_render.erase(to_rend);
}

void View::add_player_view(Player_View *pv)
{
	player_views.push_back(pv);
}


void View::render() const
{	
	Point2f topLeft(0, 0), middle(1920/2, 1200/2), bottomRight(1920,1200), ySize(0, 1200/2), xSize(1920/2, 0);

	get_Video().set_2d(make_pair(Point2f(0.0f, 0.0f), Point2f(1200.0f, 720.0f)), true);
	
	render_player(0, topLeft, middle);
	render_player(1, topLeft+xSize, middle+xSize);
	render_player(2, topLeft+ySize, middle+ySize);
	render_player(3, middle, bottomRight);
	
}

void View::render_player(int player, const Point2f &topLeft, const Point2f &bottomRight) const
{	
	player_views[player]->set_camera(topLeft,bottomRight);
	render_world();
}

// Renders the entire list of renderables to Video
void View::render_world() const 
{
	// pass each renderable into render_renderable
	for_each(to_render.begin(), to_render.end(),
		bind1st(mem_fun(&View::render_renderable), this));

}

// Render a single object
void View::render_renderable(const Seen_Object *to_rend) const
{
	Zeni::Model *m = model_map.find(to_rend->get_model_name())->second; 
	to_rend->render(m);
}

