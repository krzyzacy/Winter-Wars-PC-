#include "View.h"

#include "Renderable.h"

View::View(void)
{
}


View::~View(void)
{
}

// Renders the entire list of renderables to Video
void View::render_world() const 
{
	
}

// Render a single object
void View::render_renderable(const Renderable *to_rend) const
{
	to_rend->render((model_map[to_rend->get_model_name()]));
}

