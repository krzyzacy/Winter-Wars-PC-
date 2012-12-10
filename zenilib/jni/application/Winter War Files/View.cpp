#include "View.h"

#include "Seen_Object.h"
#include "Player_View.h"
#include "Player.h"

#include <functional>
#include <zenilib.h>

using namespace Zeni;

using namespace std;

View::View(void)
{
	model_map["snowball"] = new Zeni::Model("models/snowball.3ds");
	
// Players
	model_map["player"] = new Zeni::Model("models/blueplayer.3ds");

// Player animation
	model_map["bluegirlplayer_walk"] = new Zeni::Model("models/player/bluegirl/bluegirlwalking.3ds");
	model_map["bluegirlplayer_jump"] = new Zeni::Model("models/player/bluegirl/bluegirljumping.3ds");
	model_map["bluegirlplayer_stand"] = new Zeni::Model("models/player/bluegirl/bluegirlstanding.3ds");	
	model_map["bluegirlplayer_pack"] = new Zeni::Model("models/player/bluegirl/bluegirlpacking.3ds");
	model_map["bluegirlplayer_scoop"] = new Zeni::Model("models/player/bluegirl/bluegirlscooping.3ds");	
	model_map["bluegirlplayer_throw"] = new Zeni::Model("models/player/bluegirl/bluegirlthrowing.3ds");
	model_map["bluegirlplayer_flinch"] = new Zeni::Model("models/player/bluegirl/bluegirlflinching.3ds");	
	model_map["bluegirlplayer_die"] = new Zeni::Model("models/player/bluegirl/bluegirldying.3ds");	

	model_map["blueboyplayer_walk"] = new Zeni::Model("models/player/blueboy/blueboywalking.3ds");
	model_map["blueboyplayer_jump"] = new Zeni::Model("models/player/blueboy/blueboyjumping.3ds");
	model_map["blueboyplayer_stand"] = new Zeni::Model("models/player/blueboy/blueboystanding.3ds");	
	model_map["blueboyplayer_pack"] = new Zeni::Model("models/player/blueboy/blueboypacking.3ds");
	model_map["blueboyplayer_scoop"] = new Zeni::Model("models/player/blueboy/blueboyscooping.3ds");	
	model_map["blueboyplayer_throw"] = new Zeni::Model("models/player/blueboy/blueboythrowing.3ds");
	model_map["blueboyplayer_flinch"] = new Zeni::Model("models/player/blueboy/blueboyflinching.3ds");	
	model_map["blueboyplayer_die"] = new Zeni::Model("models/player/blueboy/blueboydying.3ds");
	
	model_map["greengirlplayer_walk"] = new Zeni::Model("models/player/greengirl/greengirlwalking.3ds");
	model_map["greengirlplayer_jump"] = new Zeni::Model("models/player/greengirl/greengirljumping.3ds");
	model_map["greengirlplayer_stand"] = new Zeni::Model("models/player/greengirl/greengirlstanding.3ds");	
	model_map["greengirlplayer_pack"] = new Zeni::Model("models/player/greengirl/greengirlpacking.3ds");
	model_map["greengirlplayer_scoop"] = new Zeni::Model("models/player/greengirl/greengirlscooping.3ds");	
	model_map["greengirlplayer_throw"] = new Zeni::Model("models/player/greengirl/greengirlthrowing.3ds");
	model_map["greengirlplayer_flinch"] = new Zeni::Model("models/player/greengirl/greengirlflinching.3ds");	
	model_map["greengirlplayer_die"] = new Zeni::Model("models/player/greengirl/greengirldying.3ds");	

	model_map["greenboyplayer_walk"] = new Zeni::Model("models/player/greenboy/greenboywalking.3ds");
	model_map["greenboyplayer_jump"] = new Zeni::Model("models/player/greenboy/greenboyjumping.3ds");
	model_map["greenboyplayer_stand"] = new Zeni::Model("models/player/greenboy/greenboystanding.3ds");	
	model_map["greenboyplayer_pack"] = new Zeni::Model("models/player/greenboy/greenboypacking.3ds");
	model_map["greenboyplayer_scoop"] = new Zeni::Model("models/player/greenboy/greenboyscooping.3ds");	
	model_map["greenboyplayer_throw"] = new Zeni::Model("models/player/greenboy/greenboythrowing.3ds");
	model_map["greenboyplayer_flinch"] = new Zeni::Model("models/player/greenboy/greenboyflinching.3ds");	
	model_map["greenboyplayer_die"] = new Zeni::Model("models/player/greenboy/greenboydying.3ds");	

	model_map["orangegirlplayer_walk"] = new Zeni::Model("models/player/orangegirl/orangegirlwalking.3ds");
	model_map["orangegirlplayer_jump"] = new Zeni::Model("models/player/orangegirl/orangegirljumping.3ds");
	model_map["orangegirlplayer_stand"] = new Zeni::Model("models/player/orangegirl/orangegirlstanding.3ds");	
	model_map["orangegirlplayer_pack"] = new Zeni::Model("models/player/orangegirl/orangegirlpacking.3ds");
	model_map["orangegirlplayer_scoop"] = new Zeni::Model("models/player/orangegirl/orangegirlscooping.3ds");	
	model_map["orangegirlplayer_throw"] = new Zeni::Model("models/player/orangegirl/orangegirlthrowing.3ds");
	model_map["orangegirlplayer_flinch"] = new Zeni::Model("models/player/orangegirl/orangegirlflinching.3ds");	
	model_map["orangegirlplayer_die"] = new Zeni::Model("models/player/orangegirl/orangegirldying.3ds");	

	model_map["orangeboyplayer_walk"] = new Zeni::Model("models/player/orangeboy/orangeboywalking.3ds");
	model_map["orangeboyplayer_jump"] = new Zeni::Model("models/player/orangeboy/orangeboyjumping.3ds");
	model_map["orangeboyplayer_stand"] = new Zeni::Model("models/player/orangeboy/orangeboystanding.3ds");	
	model_map["orangeboyplayer_pack"] = new Zeni::Model("models/player/orangeboy/orangeboypacking.3ds");
	model_map["orangeboyplayer_scoop"] = new Zeni::Model("models/player/orangeboy/orangeboyscooping.3ds");	
	model_map["orangeboyplayer_throw"] = new Zeni::Model("models/player/orangeboy/orangeboythrowing.3ds");
	model_map["orangeboyplayer_flinch"] = new Zeni::Model("models/player/orangeboy/orangeboyflinching.3ds");	
	model_map["orangeboyplayer_die"] = new Zeni::Model("models/player/orangeboy/orangeboydying.3ds");	

	model_map["redgirlplayer_walk"] = new Zeni::Model("models/player/redgirl/redgirlwalking.3ds");
	model_map["redgirlplayer_jump"] = new Zeni::Model("models/player/redgirl/redgirljumping.3ds");
	model_map["redgirlplayer_stand"] = new Zeni::Model("models/player/redgirl/redgirlstanding.3ds");	
	model_map["redgirlplayer_pack"] = new Zeni::Model("models/player/redgirl/redgirlpacking.3ds");
	model_map["redgirlplayer_scoop"] = new Zeni::Model("models/player/redgirl/redgirlscooping.3ds");	
	model_map["redgirlplayer_throw"] = new Zeni::Model("models/player/redgirl/redgirlthrowing.3ds");
	model_map["redgirlplayer_flinch"] = new Zeni::Model("models/player/redgirl/redgirlflinching.3ds");	
	model_map["redgirlplayer_die"] = new Zeni::Model("models/player/redgirl/redgirldying.3ds");	

	model_map["redboyplayer_walk"] = new Zeni::Model("models/player/redboy/redboywalking.3ds");
	model_map["redboyplayer_jump"] = new Zeni::Model("models/player/redboy/redboyjumping.3ds");
	model_map["redboyplayer_stand"] = new Zeni::Model("models/player/redboy/redboystanding.3ds");	
	model_map["redboyplayer_pack"] = new Zeni::Model("models/player/redboy/redboypacking.3ds");
	model_map["redboyplayer_scoop"] = new Zeni::Model("models/player/redboy/redboyscooping.3ds");	
	model_map["redboyplayer_throw"] = new Zeni::Model("models/player/redboy/redboythrowing.3ds");
	model_map["redboyplayer_flinch"] = new Zeni::Model("models/player/redboy/redboyflinching.3ds");	
	model_map["redboyplayer_die"] = new Zeni::Model("models/player/redboy/redboydying.3ds");	

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
	//Fortress Animations
	model_map["bluefortress_spin"] = new Zeni::Model("models/fortress/fortressbluespinning.3ds");
	model_map["greenfortress_spin"] = new Zeni::Model("models/fortress/fortressgreenspinning.3ds");
	model_map["redfortress_spin"] = new Zeni::Model("models/fortress/fortressredspinning.3ds");
	model_map["orangefortress_spin"] = new Zeni::Model("models/fortress/fortressorangespinning.3ds");

	model_map["bluefortress_isolated"] = new Zeni::Model("models/fortress/fortressblueisolated.3ds");
	model_map["greenfortress_isolated"] = new Zeni::Model("models/fortress/fortressgreenisolated.3ds");
	model_map["redfortress_isolated"] = new Zeni::Model("models/fortress/fortressredisolated.3ds");
	model_map["orangefortress_isolated"] = new Zeni::Model("models/fortress/fortressorangeisolated.3ds");

	//Snowman Animations
	model_map["bluesnowman_stand"] = new Zeni::Model("models/snowman/bluesnowman/bluesnowmanstanding.3ds");
	model_map["greensnowman_stand"] = new Zeni::Model("models/snowman/greensnowman/greensnowmanstanding.3ds");
	model_map["redsnowman_stand"] = new Zeni::Model("models/snowman/redsnowman/redsnowmanstanding.3ds");
	model_map["orangesnowman_stand"] = new Zeni::Model("models/snowman/orangesnowman/orangesnowmanstanding.3ds");

	model_map["bluesnowman_throw_left"] = new Zeni::Model("models/snowman/bluesnowman/bluesnowmanthrowingleft.3ds");
	model_map["greensnowman_throw_left"] = new Zeni::Model("models/snowman/greensnowman/greensnowmanthrowingleft.3ds");
	model_map["redsnowman_throw_left"] = new Zeni::Model("models/snowman/redsnowman/redsnowmanthrowingleft.3ds");
	model_map["orangesnowman_throw_left"] = new Zeni::Model("models/snowman/orangesnowman/orangesnowmanthrowingleft.3ds");

	model_map["bluesnowman_throw_right"] = new Zeni::Model("models/snowman/bluesnowman/bluesnowmanthrowingright.3ds");
	model_map["greensnowman_throw_right"] = new Zeni::Model("models/snowman/greensnowman/greensnowmanthrowingright.3ds");
	model_map["redsnowman_throw_right"] = new Zeni::Model("models/snowman/redsnowman/redsnowmanthrowingright.3ds");
	model_map["orangesnowman_throw_right"] = new Zeni::Model("models/snowman/orangesnowman/orangesnowmanthrowingright.3ds");

	model_map["bluesnowman_isolated"] = new Zeni::Model("models/snowman/bluesnowman/bluesnowmanisolated.3ds");
	model_map["greensnowman_isolated"] = new Zeni::Model("models/snowman/greensnowman/greensnowmanisolated.3ds");
	model_map["redsnowman_isolated"] = new Zeni::Model("models/snowman/redsnowman/redsnowmanisolated.3ds");
	model_map["orangesnowman_isolated"] = new Zeni::Model("models/snowman/orangesnowman/orangesnowmanisolated.3ds");
/*
	model_map["blue_snowfactory"] = new Zeni::Model("models/snowfactory/bluesnowfactory.3ds");
	model_map["green_snowfactory"] = new Zeni::Model("models/snowfactory/greensnowfactory.3ds");
	model_map["red_snowfactory"] = new Zeni::Model("models/snowfactory/redsnowfactory.3ds");
	model_map["orange_snowfactory"] = new Zeni::Model("models/snowfactory/orangesnowfactory.3ds");
*/
	//Factory Animation
	model_map["bluefactory_spin"] = new Zeni::Model("models/snowfactory/bluesnowfactoryspin.3ds");
	model_map["greenfactory_spin"] = new Zeni::Model("models/snowfactory/greensnowfactoryspin.3ds");
	model_map["redfactory_spin"] = new Zeni::Model("models/snowfactory/redsnowfactoryspin.3ds");
	model_map["orangefactory_spin"] = new Zeni::Model("models/snowfactory/orangesnowfactoryspin.3ds");

	model_map["bluefactory_isolated"] = new Zeni::Model("models/snowfactory/bluesnowfactoryisolated.3ds");
	model_map["greenfactory_isolated"] = new Zeni::Model("models/snowfactory/greensnowfactoryisolated.3ds");
	model_map["redfactory_isolated"] = new Zeni::Model("models/snowfactory/redsnowfactoryisolated.3ds");
	model_map["orangefactory_isolated"] = new Zeni::Model("models/snowfactory/orangesnowfactoryisolated.3ds");

	//Healing Pool Animation
	model_map["bluehealing_pool_isolated"] = new Zeni::Model("models/healingpool/bluehealingpoolisolated.3ds");
	model_map["greenhealing_pool_isolated"] = new Zeni::Model("models/healingpool/greenhealingpoolisolated.3ds");
	model_map["redhealing_pool_isolated"] = new Zeni::Model("models/healingpool/redhealingpoolisolated.3ds");
	model_map["orangehealing_pool_isolated"] = new Zeni::Model("models/healingpool/orangehealingpoolisolated.3ds");
	
	model_map["bluehealing_pool_heal"] = new Zeni::Model("models/healingpool/bluehealingpoolhealing.3ds");
	model_map["greenhealing_pool_heal"] = new Zeni::Model("models/healingpool/greenhealingpoolhealing.3ds");
	model_map["redhealing_pool_heal"] = new Zeni::Model("models/healingpool/redhealingpoolhealing.3ds");
	model_map["orangehealing_pool_heal"] = new Zeni::Model("models/healingpool/orangehealingpoolhealing.3ds");

	//Christmas Tree Animations
	model_map["bluetree_unowned"] = new Zeni::Model("models/chirstmastree/christmastreeblueowned1.3ds");
	model_map["greentree_unowned"] = new Zeni::Model("models/chirstmastree/christmastreegreenowned1.3ds");
	model_map["redtree_unowned"] = new Zeni::Model("models/chirstmastree/christmastreeredowned.3ds");
	model_map["orangetree_unowned"] = new Zeni::Model("models/chirstmastree/christmastreeorangeowned.3ds");
	model_map["tree_unowned"] = new Zeni::Model("models/chirstmastree/christmastreeunowned.3ds");

	model_map["bluetree_owned"] = new Zeni::Model("models/chirstmastree/christmastreeblueowned1.3ds");
	model_map["greentree_owned"] = new Zeni::Model("models/chirstmastree/christmastreegreenowned1.3ds");
	model_map["redtree_owned"] = new Zeni::Model("models/chirstmastree/christmastreeredowned.3ds");
	model_map["orangetree_owned"] = new Zeni::Model("models/chirstmastree/christmastreeorangeowned.3ds");

	//Pesent animations
	model_map["bluepresent_wrapped"] = new Zeni::Model("models/present/bluepresentwrapped.3ds");
	model_map["greenpresent_wrapped"] = new Zeni::Model("models/present/greenpresentwrapped.3ds");
	model_map["redpresent_wrapped"] = new Zeni::Model("models/present/redpresentwrapped.3ds");
	model_map["orangepresent_wrapped"] = new Zeni::Model("models/present/orangepresentwrapped.3ds");

	model_map["bluepresent_unwrapped"] = new Zeni::Model("models/present/bluepresentunwrapped.3ds");
	model_map["greenpresent_unwrapped"] = new Zeni::Model("models/present/greenpresentunwrapped.3ds");
	model_map["redpresent_unwrapped"] = new Zeni::Model("models/present/redpresentunwrapped.3ds");
	model_map["orangepresent_unwrapped"] = new Zeni::Model("models/present/orangepresentunwrapped.3ds");

	model_map["explode"] = new Zeni::Model("models/hiteffect/hiteffect.3ds");

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

Player_View *cur_View; // The current player we are viewing
				// DONT TOUCH IF YOU DON"T KNOW WHAT YOU ARE DOING!

void View::render_player(int player, const Point2f &topLeft, const Point2f &bottomRight) const
{	
	Video &vr = get_Video();
	//vr.set_3d(cur_View->get_player()->);
	cur_View = player_views[player];  // this is the cur player
	player_views[player]->set_camera(topLeft,bottomRight);

	Vertex3f_Texture c_p0(Point3f(0.0f,0.0f,1000.0f),                             Point2f(0.0f, 0.0f));
    Vertex3f_Texture c_p1(Point3f(0.0f,2500.0f,1000.0f),                             Point2f(0.0f, 1.0f));
    Vertex3f_Texture c_p2(Point3f(2500.0f,2500.0f,1000.0f),                             Point2f(1.0f, 1.0f)); 
    Vertex3f_Texture c_p3(Point3f(2500.0f,0.0f,1000.0f),                             Point2f(1.0f, 0.0f));
    Material c_material("Nlight");
      
    Quadrilateral<Vertex3f_Texture> c_quad(c_p0, c_p1, c_p2, c_p3);
    c_quad.fax_Material(&c_material);
      
    vr.render(c_quad);

	for(int i = 0 ; i < 4; i++){
		float xx, yy;
		Material w_material("Background");

		if(i == 0){
			Vertex3f_Texture w_p0(Point3f(0.0f,0.0f,1000.0f),                             Point2f(0.0f, 0.0f));
			Vertex3f_Texture w_p1(Point3f(0.0f,0.0f,-250.0f),                             Point2f(0.0f, 1.0f));
			Vertex3f_Texture w_p2(Point3f(0.0f,2500.0f,-250.0f),                              Point2f(1.0f, 1.0f)); 
			Vertex3f_Texture w_p3(Point3f(0.0f,2500.0f,1000.0f),                              Point2f(1.0f, 0.0f));
			Quadrilateral<Vertex3f_Texture> w_quad(w_p0, w_p1, w_p2, w_p3);
			w_quad.fax_Material(&w_material);
			vr.render(w_quad);
		}
		else if(i == 1){
			Vertex3f_Texture w_p0(Point3f(0.0f,2500.0f,1000.0f),                             Point2f(0.0f, 0.0f));
			Vertex3f_Texture w_p1(Point3f(0.0f,2500.0f,-250.0f),                             Point2f(0.0f, 1.0f));
			Vertex3f_Texture w_p2(Point3f(2500.0f,2500.0f,-250.0f),                              Point2f(1.0f, 1.0f)); 
			Vertex3f_Texture w_p3(Point3f(2500.0f,2500.0f,1000.0f),                              Point2f(1.0f, 0.0f));
			Quadrilateral<Vertex3f_Texture> w_quad(w_p0, w_p1, w_p2, w_p3);
			w_quad.fax_Material(&w_material);
			vr.render(w_quad);
		}
		else if(i == 2){
			Vertex3f_Texture w_p0(Point3f(2500.0f,2500.0f,1000.0f),                             Point2f(0.0f, 0.0f));
			Vertex3f_Texture w_p1(Point3f(2500.0f,2500.0f,-250.0f),                             Point2f(0.0f, 1.0f));
			Vertex3f_Texture w_p2(Point3f(2500.0f,0.0f,-250.0f),                              Point2f(1.0f, 1.0f)); 
			Vertex3f_Texture w_p3(Point3f(2500.0f,0.0f,1000.0f),                              Point2f(1.0f, 0.0f));
			Quadrilateral<Vertex3f_Texture> w_quad(w_p0, w_p1, w_p2, w_p3);
			w_quad.fax_Material(&w_material);
			vr.render(w_quad);
		}
		else if(i == 3){
			Vertex3f_Texture w_p0(Point3f(2500.0f,0.0f,1000.0f),                             Point2f(0.0f, 0.0f));
			Vertex3f_Texture w_p1(Point3f(2500.0f,0.0f,-250.0f),                             Point2f(0.0f, 1.0f));
			Vertex3f_Texture w_p2(Point3f(0.0f,0.0f,-250.0f),                              Point2f(1.0f, 1.0f)); 
			Vertex3f_Texture w_p3(Point3f(0.0f,0.0f,1000.0f),                              Point2f(1.0f, 0.0f));
			Quadrilateral<Vertex3f_Texture> w_quad(w_p0, w_p1, w_p2, w_p3);
			w_quad.fax_Material(&w_material);
			vr.render(w_quad);
		}
		
	}



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
	// background

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
	
	// don't render the current player
	if (cur_View->get_player() == to_rend)
		return;

	to_rend->render(mIt->second);
}

