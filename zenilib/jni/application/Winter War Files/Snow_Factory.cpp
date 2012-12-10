#include "Snow_Factory.h"
#include "Team.h"
#include "Tile.h"
#include "Game_Model.h"
#include "World.h"

using namespace std;
using namespace Zeni;

Snow_Factory::Snow_Factory(Team *team, Tile* tile_,
				const Zeni::Point3f &base_) :
	Structure(team, tile_, base_, 50.0f)
{
	create_body();
	list<Tile*> family = Game_Model::get().get_World()->Get_Family(hex);
	for(list<Tile*>::iterator it = family.begin(); it != family.end(); ++it)	{
		(*it)->set_covering(SOFT_SNOW);
	}
	hex->set_covering(SOFT_SNOW);
	Health = Struct_Integrity[SNOW_FACTORY];

	animation_state = new Factory_spin();
}


Snow_Factory::~Snow_Factory(void)
{

}

void Snow_Factory::update(const float &time)
{
	if(Status == DESTROYED)	{
		hex->set_covering(ICE);
		//First sets the covering of all the tiles to randomly Ice or snow
		list<Tile*> nuc_family = Game_Model::get().get_World()->Get_Family(hex);
		for(list<Tile*>::iterator it = nuc_family.begin(); it != nuc_family.end(); ++it)	{
			if((*it) == 0) continue;
			int randomcov = rand() %2;
			if(randomcov == 0) (*it)->set_covering(ICE);
			if(randomcov == 1) (*it)->set_covering(HARD_SNOW);
		}

		//Then, iff they are double covered, turns back to soft snow
		nuc_family.push_back(hex);
		for(list<Tile*>::iterator it = nuc_family.begin(); it != nuc_family.end(); ++it)	{
			if((*it) != hex && (*it)->has_building() && (*it)->get_building()->is_snow_maker())	{
				(*it)->set_covering(SOFT_SNOW);
				continue;
			}
			list<Tile*> ext_fam = Game_Model::get().get_World()->Get_Family(*it);
			for(list<Tile*>::iterator efit = ext_fam.begin(); efit != ext_fam.end(); ++efit)	{
				if((*efit) != hex && (*efit)->has_building())	{
					if((*efit)->get_building()->is_snow_maker())	{
						(*it)->set_covering(SOFT_SNOW);
						break;
					}
				}
			}
		}
	}

	if (Connected_to_Team)
		switch_state(FAC_SPIN);
	else
		switch_state(FAC_ISO);

	Structure::update(time);
}

const model_key_t Snow_Factory::get_model_name() const 
{
	string Teamname;
		switch(owner->get_Team_Index())	{
	case BLUE:
		Teamname = "blue";
		break;
	case GREEN:
		Teamname = "green";
		break;
	case RED:
		Teamname = "red";
		break;
	case ORANGE:
		Teamname = "orange";
		break;
	default:
		Teamname = "blue";
		break;
	}
	return Teamname + animation_state->get_model_name();
}

void Snow_Factory::create_body()	{
	Point3f Top = Seen_Object::get_top_center();
	Point3f Bot = Seen_Object::get_bottom_center();
	body = Zeni::Collision::Capsule(Top, Bot, size.z/3);
}

Animator *Snow_Factory::get_animator() const
{
	return animation_state;
}