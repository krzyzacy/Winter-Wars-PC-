#include "Moveable.h"
#include "World.h"
#include "Game_Model.h"
#include "Tile.h"

using namespace std;
using namespace Zeni;


const Zeni::Vector3f grav_accel(0.0f, 0.0f, -250.0f);

Moveable::Moveable(const Point3f &center_, const Vector3f &size_ ) :
	Seen_Object(center_, size_)
	, velocity(Vector3f(0,0,0))
{
}


Moveable::~Moveable(void)
{
}

void Moveable::gravity(const float &time)	{
	if(!is_on_ground())
		velocity += grav_accel * time;
	else
		on_ground();

}

void Moveable::update(const float &time)	{
	Collidable::update(time);

	gravity(time);
	

	center += velocity * time;

	Vector3f player_pos(center);

	if (Game_Model::get().get_World()->get_tile(center) == NULL){
		off_map();
	}
	/*else if (Game_Model::get().get_World()->get_ground_height(center) 
				>= get_bottom_center().z + 10.0f){
		hit_tile();
	}*/
	else{

		for(double i = -100.0; i <= 100.0; i = i + 10){
			Vector3f pos_dir(i / 100, sqrt(1 - (i / 100) * (i / 100)), 0);
			Vector3f neg_dir(i / 100, - sqrt(1 - (i / 100) * (i / 100)), 0);

			if(Game_Model::get().get_World()->get_tile(Point3f(player_pos + pos_dir * size.x / 2 )) == NULL){
				off_map();
				return;
			}
			else if(Game_Model::get().get_World()->get_ground_height(Point3f(player_pos + pos_dir * size.x / 2 )) >= get_bottom_center().z + 10.0f){
				hit_tile();
				return;
			}

			if(Game_Model::get().get_World()->get_tile(Point3f(player_pos + neg_dir * size.x / 2 )) == NULL){
				off_map();
				return;
			}
			else if(Game_Model::get().get_World()->get_ground_height(Point3f(player_pos + neg_dir * size.x / 2 )) >= get_bottom_center().z + 10.0f){
				hit_tile();
				return;
			}
		}
	}
}

void Moveable::set_velocity(const Vector3f &vel)	{
	velocity = vel;
}

void Moveable::accelerate(const Vector3f &acc, const float &time)	{
	velocity += acc * time;
}

void Moveable::network_overwrite_members(Zeni::Point3f &pos, Zeni::Vector3f &vel)	{
	center = pos;
	velocity = vel;
}


