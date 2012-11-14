#include "View.h"

#include "Seen_Object.h"

#include <functional>

using namespace std;

View::View(void)
{
	model_map["snowball"] = new Zeni::Model("models/snowball.3ds");
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



void View::render()
{
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

