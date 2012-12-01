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
	
// Players
	model_map["player"] = new Zeni::Model("models/blueplayer.3ds");
	
// Tiles
	model_map["neutralsoftsnowtile"] = new Zeni::Model("models/softsnow/neutralsoftsnowtile.3ds");
	model_map["neutralhardsnowtile"] = new Zeni::Model("models/hardsnow/neutralhardsnowtile.3ds");
	model_map["neutralicetile"] = new Zeni::Model("models/ice/neutralicetile.3ds");
	model_map["greensoftsnowtile"] = new Zeni::Model("models/softsnow/greensoftsnowtile.3ds");
	model_map["greenhardsnowtile"] = new Zeni::Model("models/hardsnow/greenhardsnowtile.3ds");
	model_map["greenicetile"] = new Zeni::Model("models/ice/greenicetile.3ds");
	model_map["redsoftsnowtile"] = new Zeni::Model("models/softsnow/redsoftsnowtile.3ds");
	model_map["redhardsnowtile"] = new Zeni::Model("models/hardsnow/redhardsnowtile.3ds");
	model_map["redicetile"] = new Zeni::Model("models/ice/redicetile.3ds");
	model_map["bluesoftsnowtile"] = new Zeni::Model("models/softsnow/bluesoftsnowtile.3ds");
	model_map["bluehardsnowtile"] = new Zeni::Model("models/hardsnow/bluehardsnowtile.3ds");
	model_map["blueicetile"] = new Zeni::Model("models/ice/blueicetile.3ds");
	model_map["orangesoftsnowtile"] = new Zeni::Model("models/softsnow/orangesoftsnowtile.3ds");
	model_map["orangehardsnowtile"] = new Zeni::Model("models/hardsnow/orangehardsnowtile.3ds");
	model_map["orangeicetile"] = new Zeni::Model("models/ice/orangeicetile.3ds");
	
// Structures	
	model_map["blue_fort"] = new Zeni::Model("models/fortress/fortressblue.3ds");
	model_map["green_fort"] = new Zeni::Model("models/fortress/fortressgreen.3ds");
	model_map["red_fort"] = new Zeni::Model("models/fortress/fortressred.3ds");
	model_map["orange_fort"] = new Zeni::Model("models/fortress/fortressorange.3ds");

	model_map["blue_snowman"] = new Zeni::Model("models/snowman/bluesnowman.3ds");
	model_map["green_snowman"] = new Zeni::Model("models/snowman/greensnowman.3ds");
	model_map["red_snowman"] = new Zeni::Model("models/snowman/redsnowman.3ds");
	model_map["orange_snowman"] = new Zeni::Model("models/snowman/orangesnowman.3ds");

	model_map["blue_snowfactory"] = new Zeni::Model("models/snowfactory/bluesnowfactory.3ds");
	model_map["green_snowfactory"] = new Zeni::Model("models/snowfactory/greensnowfactory.3ds");
	model_map["red_snowfactory"] = new Zeni::Model("models/snowfactory/redsnowfactory.3ds");
	model_map["orange_snowfactory"] = new Zeni::Model("models/snowfactory/orangesnowfactory.3ds");

	model_map["blue_healingpool"] = new Zeni::Model("models/healingpool/bluehealingpool.3ds");
	model_map["green_healingpool"] = new Zeni::Model("models/healingpool/greenhealingpool.3ds");
	model_map["red_healingpool"] = new Zeni::Model("models/healingpool/redhealingpool.3ds");
	model_map["orange_healingpool"] = new Zeni::Model("models/healingpool/orangehealingpool.3ds");

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
	int width = get_Window().get_width();
	int height = get_Window().get_height();

	Point2f topLeft(0, 0), middle(width/2, height/2), bottomRight(width,height), ySize(0, height/2), xSize(width/2, 0);


	render_player(0, topLeft, middle);
	render_player(1, topLeft+xSize, middle+xSize);
	render_player(2, topLeft+ySize, middle+ySize);
	render_player(3, middle, bottomRight);

	get_Video().set_2d(make_pair(Point2f(0.0f, 0.0f), Point2f(width, height)), true);
	
	render_player_hud(0, topLeft, middle);
	render_player_hud(1, topLeft+xSize, middle+xSize);
	render_player_hud(2, topLeft+ySize, middle+ySize);
	render_player_hud(3, middle, bottomRight);
	
}

void View::render_player(int player, const Point2f &topLeft, const Point2f &bottomRight) const
{	
	player_views[player]->set_camera(topLeft,bottomRight);
	render_world();

}

void View::render_player_hud(int player, const Point2f &topLeft, const Point2f &bottomRight) const
{	
	// render the player's hud
	player_views[player]->render_hud(topLeft,bottomRight);
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
	map<model_key_t, Model *>::const_iterator mIt = model_map.find(to_rend->get_model_name()); 

	if (mIt == model_map.end())
		throw Error(("Model " + to_rend->get_model_name() + " does not exist.").data());

	to_rend->render(mIt->second);
}

