#include "View.h"

#include "Seen_Object.h"
#include "Player_View.h"

#include <functional>

using namespace std;

View::View(void)
{
	model_map["snowball"] = new Zeni::Model("models/snowball.3ds");
	model_map["simpletile"] = new Zeni::Model("models/simpletile.3ds");

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
	for( int i = 0 ; i < player_views.size() ; i++)
	{
		player_views[i]->set_camera();
		render_world();

	}
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

