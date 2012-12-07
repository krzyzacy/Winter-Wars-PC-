#include "Structure.h"
#include "Snowball.h"
#include "Team.h"
#include "Tile.h"
#include "Player.h"

using namespace Zeni;

const int Structure::structure_ID_c = 3;

Structure::Structure(Team *team, Tile* tile_,
				const Zeni::Point3f &position_,	 float radius) :
	Seen_Object(position_, Vector3f(1,1,1)*radius),
	owner(team), Health(1), Status(PRESENT_MODE), 
	Connected_to_Team(true), hex(tile_)
{
	//Magic number shift height attempt
	center.z += radius/2;
}


Structure::~Structure(void)
{
}

void Structure::receive_hit(Snowball* S)	{
	if(S->Snow_man_Generated())
		return;
		
	if(S->get_Team_Index() == hex->get_team())	{
		S->deal_damage();
		return;
	}

	Health -= S->deal_damage();
	if(Health < 0)
		Status = DESTROYED;
}

void Structure::update(const float &time)
{
	//Structures don't move, so their body doen't need to be changed.
	//Collidable::update(time);
	if(Status == DESTROYED)	{
		perform_destruction_effects();
		hex->destroy_structure();
		owner->remove_tile(hex);
	}
}

void Structure::perform_destruction_effects()	{
	

}

void Structure::handle_player_collision(Player *P)	{
	//Should be overwritten by each
	//However fort and factory, for now do the same thing
	P->push_away_from(center, 25);
}

void Structure::create_body()		{
	Point3f Top = Seen_Object::get_top_center();
	Point3f Bot = Seen_Object::get_bottom_center();
	body = Zeni::Collision::Capsule(Top, Bot, size.z/2);
}

void Structure::change_height(const float &delta)	{
	center.z += delta;
}

Animator *Structure::get_animator() const {
	return 0;
}

void Structure::switch_state(StructureEvent_e sevent)
{
	StructureAnimator *next = animation_state->get_next(sevent);
	if (next)
	{
		delete animation_state;
		animation_state = next;
	}
}