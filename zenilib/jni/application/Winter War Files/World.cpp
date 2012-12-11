#include "World.h"

#include "Game_Model.h"
#include "View.h"
#include "Tile.h"
#include "Player.h"

using namespace std;
using namespace Zeni;



const float Ice_friction = 0.05;
const float Norml_friction = 0.2;

const float Tile_Move_Speed = 50;

World::World( View *view_,
		const int width__,
		const int height__,
		const float hex_length__
		) :
	map(height__, vector<Tile *>(width__, 0) ),
	view(view_)
{
	map_width = width__ - 1;
	map_height = height__ - 1;
	cur_team_count = 0;

	tile_size = hex_length__;

	float tR = sqrt(3.0f) * tile_size / 2;
	float tS = tile_size;
	float tH = tile_size / 2; 

	for(int h = 0; h < map_height; h++){
		for(int w = 0; w < map_width; w++){

			Zeni::Point3f center;
			center.x = w * tR * 2 + tR;
			if(h % 2 == 1) center.x += tR;
			
			center.y = h * (tH + tS) + tS;
			center.z = 0.0f;
			if(h == 0 || h == map_height - 1 || w == 0 || w == map_width - 1)
				center.z = tile_size * 1.7;

			if((abs(6 - h) + abs(7 - w)) < 4){
				center.z += 0.6 * tile_size;
			}
			else if((abs(6 - h) + abs(7 - w)) < 7){
				center.z += 0.2 * tile_size;
			}
			
			float scale_size = 2.0*tile_size;

			Tile* tmp;

			if(h == 0 || h == map_height - 1 || w == 0 || w == map_width - 1)
				tmp = new Tile(tile_size,center,Zeni::Vector3f(scale_size,scale_size,1.2 * scale_size),w,h);
			else
				tmp = new Tile(tile_size,center,Zeni::Vector3f(scale_size,scale_size,scale_size),w,h);

			if((abs(6 - h) + abs(7 - w)) < 4){
				tmp->set_covering(ICE);
			}
			else if((abs(6 - h) + abs(7 - w)) < 7){
				int randomcover = rand() % 3;

				if(randomcover == 0) tmp->set_covering(SOFT_SNOW);
				if(randomcover == 1) tmp->set_covering(HARD_SNOW);
				if(randomcover == 2) tmp->set_covering(ICE);
			}
			else{
				int randomcover = rand() % 2;
				if(randomcover == 0) tmp->set_covering(SOFT_SNOW);
				if(randomcover == 1) tmp->set_covering(HARD_SNOW);
			}

			/*
			int randomcover = rand() % 3;
			
			int randomteam = rand() % 5;

			if(randomteam == 0) tmp->set_team(NEUTRAL);
			if(randomteam == 1) tmp->set_team(GREEN);
			if(randomteam == 2) tmp->set_team(RED);
			if(randomteam == 3) tmp->set_team(BLUE);
			if(randomteam == 4) tmp->set_team(ORANGE);
			if(randomcover == 0) tmp->set_covering(SOFT_SNOW);
			if(randomcover == 1) tmp->set_covering(HARD_SNOW);
			if(randomcover == 2) tmp->set_covering(ICE);
			//tmp->set_covering(ICE);
			*/

			tmp->set_team(NEUTRAL);
			
			map[h][w] = tmp;

			view->add_renderable(map[h][w]);

		}
	}
}


World::~World(void)
{
}


Tile* World::get_tile(const Zeni::Point3f &position){
	float xr = position.x;
	float yr = position.y;

	if(xr < 0 || yr < 0){
		return NULL;
	}

	float tR = sqrt(3.0f) * tile_size / 2;
	float tS = tile_size;
	float tH = tile_size / 2; 

	// "slice" the map as squares - type A and type B
	// and adjust the vector index accordingly
	
	int sec_x = xr / (2 * tR);
	int sec_y = yr / (tS + tH);

	if((sec_y % 2 == 0 && sec_x >= map_width) || sec_x > map_width || sec_y >= map_height)
		return NULL;

	xr -= sec_x * 2 * tR;
	yr -= sec_y * (tS + tH);

	if(sec_y % 2 == 0){ // odd row, section A
		if(yr >= tH){
				return map[sec_y][sec_x];
		}
		else if(xr >= tR){
			if(yr <= (sqrt(3.0f) / 3 ) * (xr - tR) ){
				if(sec_y != 0)
					return map[sec_y - 1][sec_x];
				else
					return NULL;
			}
			else{
					return map[sec_y][sec_x];
			}
		}
		else{
			if(yr <= (-(sqrt(3.0f) * xr)/3 + tH)){
				if(sec_y != 0 && sec_x != 0)
					return map[sec_y - 1][sec_x - 1];
				else
					return NULL;
			}
			else{
					return map[sec_y][sec_x];
			}
		}
	}
	else{ // even row, section B (sec_y == map_height - 1 == 13)
		if(xr >= tR){
			if(yr >= tH){
					if(sec_x != map_width){
						return map[sec_y][sec_x];
					}
					else
						return NULL;
			}
			else{
				if(yr <= (-(sqrt(3.0f) * (xr - tR))/3 + tH)){
					if(sec_y != 0 && sec_x != map_width)
						return map[sec_y - 1][sec_x];
					else
						return NULL;
				}
				else{
					//if(sec_x != map_width)
						return map[sec_y][sec_x];
					//else
						//return NULL;
				}
			}
		}
		else{
			if(yr >= tH){
				if(sec_x != 0)
					return map[sec_y][sec_x - 1];
				else
					return NULL;
			}
			else{
				if(yr <= (sqrt(3.0f) / 3 ) * xr ){
					if(sec_y != 0 && sec_x != map_width)
						return map[sec_y - 1][sec_x];
					else
						return NULL;
				}
				else{
					if(sec_x != 0)
						return map[sec_y][sec_x - 1];
					else
						return NULL;
				}
			}
		}
	}
}

Tile * World::get_tile(int row, int col){
	return map[row][col];
}

bool World::is_adjacent(Tile* A, Tile* B){
	int row_A = A->get_row();
	int row_B = B->get_row();
	int col_A = A->get_col();
	int col_B = B->get_col();

	if(abs(row_A - row_B) > 1 || abs(col_A - col_B) > 1)
		return false;

	if(row_A % 2 == 0){
		if(col_B - col_A == 1)
			return false;
	}
	
	if(row_A % 2 == 1){
		if(col_A - col_B == 1)
			return false;
	}
	
	return true;
}


/* haven't tested.. should be working.. */
std::list<Tile*> World::Get_Family(Tile *Central){
	std::list<Tile *> ret;

	if(Central->get_col() != 0)
		ret.push_back(map[Central->get_row()][Central->get_col() - 1]);

	if(Central->get_col() != map_width - 1)
		ret.push_back(map[Central->get_row()][Central->get_col() + 1]);

	if(Central->get_row() % 2 == 0){
		if(Central->get_row() == 0){
			if(Central->get_col() == 0){
				ret.push_back(map[Central->get_row() + 1][Central->get_col()]);
			}
			else{
				ret.push_back(map[Central->get_row() + 1][Central->get_col()]);
				ret.push_back(map[Central->get_row() + 1][Central->get_col() - 1]);
			}
		}
		else if(Central->get_row() == map_height - 1){
			if(Central->get_col() == 0){
				ret.push_back(map[Central->get_row() - 1][Central->get_col()]);
			}
			else{
				ret.push_back(map[Central->get_row() - 1][Central->get_col()]);
				ret.push_back(map[Central->get_row() - 1][Central->get_col() - 1]);
			}
		}
		else{
			if(Central->get_col() == 0){
				ret.push_back(map[Central->get_row() - 1][Central->get_col()]);
				ret.push_back(map[Central->get_row() + 1][Central->get_col()]);
			}
			else{
				ret.push_back(map[Central->get_row() - 1][Central->get_col()]);
				ret.push_back(map[Central->get_row() - 1][Central->get_col() - 1]);
				ret.push_back(map[Central->get_row() + 1][Central->get_col()]);
				ret.push_back(map[Central->get_row() + 1][Central->get_col() - 1]);
			}
		}
	}
	else{
		if(Central->get_row() == map_height - 1){
			if(Central->get_col() == map_width - 1){
				ret.push_back(map[Central->get_row() - 1][Central->get_col()]);
			}
			else{
				ret.push_back(map[Central->get_row() - 1][Central->get_col()]);
				ret.push_back(map[Central->get_row() - 1][Central->get_col() + 1]);
			}
		}
		else{
			if(Central->get_col() == map_width - 1){
				ret.push_back(map[Central->get_row() - 1][Central->get_col()]);
				ret.push_back(map[Central->get_row() + 1][Central->get_col()]);
			}
			else{
				ret.push_back(map[Central->get_row() - 1][Central->get_col()]);
				ret.push_back(map[Central->get_row() - 1][Central->get_col() + 1]);
				ret.push_back(map[Central->get_row() + 1][Central->get_col()]);
				ret.push_back(map[Central->get_row() + 1][Central->get_col() + 1]);
			}
		}
	}

	return ret;
}


Tile * World::get_next_Base_Tile()	{
	cur_team_count++;
	switch(cur_team_count)	{
	case 1:
		return map[1][1];
	case 2:
		return map[map_height - 2][map_width - 2];
	case 3:
		return map[map_height - 2][1];
	case 4:
		return map[1][map_width - 2];
	default:
		return 0;
	}
	
}

Tile * World::player_is_looking_at(const Point3f &player_pos, Vector3f look_Dir)	{
	//&&& Basic for now, to allow for testing
	//If the player is "looking" to far away, like level across the board, then
	//just return the tile next to them in that direction

	if(look_Dir.x >= sqrt(3.0f) / 2){ // right
		if(get_tile(player_pos)->get_col() != map_width - 1)
			return map[get_tile(player_pos)->get_row()][get_tile(player_pos)->get_col() + 1];
		else
			return NULL;
	}
	else if(look_Dir.x <= - sqrt(3.0f) / 2){ // left
		if(get_tile(player_pos)->get_col() != 0)
			return map[get_tile(player_pos)->get_row()][get_tile(player_pos)->get_col() - 1];
		else
			return NULL;
	}
	else if((look_Dir.x <= sqrt(3.0f) / 2 && look_Dir.x >= 0) && look_Dir.y <= 0 ){ // upright
		if(get_tile(player_pos)->get_row() == 0)
			return NULL;
		else if(get_tile(player_pos)->get_row() % 2 == 1){
			if(get_tile(player_pos)->get_col() == map_width - 1){
				return NULL;
			}
			else{
				return map[get_tile(player_pos)->get_row() - 1][get_tile(player_pos)->get_col() + 1];
			}
		}
		else
			return map[get_tile(player_pos)->get_row() - 1][get_tile(player_pos)->get_col()];	
	}
	else if((look_Dir.x >= - sqrt(3.0f) / 2 && look_Dir.x <= 0) && look_Dir.y <= 0 ){ // upleft
		if(get_tile(player_pos)->get_row() == 0)
			return NULL;
		else if(get_tile(player_pos)->get_row() % 2 == 0){
			if(get_tile(player_pos)->get_col() == 0){
				return NULL;
			}
			else{
				return map[get_tile(player_pos)->get_row() - 1][get_tile(player_pos)->get_col() - 1];
			}
		}
		else
			return map[get_tile(player_pos)->get_row() - 1][get_tile(player_pos)->get_col()];
	}
	else if((look_Dir.x <= sqrt(3.0f) / 2 && look_Dir.x >= 0) && look_Dir.y >= 0 ){ // lowerright
		if(get_tile(player_pos)->get_row() == map_height)
			return NULL;
		else if(get_tile(player_pos)->get_row() % 2 == 1){
			if(get_tile(player_pos)->get_col() == map_width - 1){
				return NULL;
			}
			else{
				return map[get_tile(player_pos)->get_row() + 1][get_tile(player_pos)->get_col() + 1];
			}
		}
		else
			return map[get_tile(player_pos)->get_row() + 1][get_tile(player_pos)->get_col()];
			
	}
	else if((look_Dir.x >= - sqrt(3.0f) / 2 && look_Dir.x <= 0) && look_Dir.y >= 0 ){ // lowerleft
		if(get_tile(player_pos)->get_row() == map_height)
			return NULL;
		else if(get_tile(player_pos)->get_row() % 2 == 0){
			if(get_tile(player_pos)->get_col() == 0){
				return NULL;
			}
			else{
				return map[get_tile(player_pos)->get_row() + 1][get_tile(player_pos)->get_col() - 1];
			}
		}
		else
			return map[get_tile(player_pos)->get_row() + 1][get_tile(player_pos)->get_col()];
	}
	else
		return NULL;
}

void World::raise_tile(Point3f location)	{
	//Add ownership restrictions to this later
	Tile* ti = get_tile(location);
	float delta = Game_Model::get().get_time_step() * Tile_Move_Speed;
	if(ti->set_height(delta))	{
		for(int i = 0; i < 4; i++)	{
			if(get_tile(Game_Model::get().get_player(i)->get_posistion()) == ti)
				Game_Model::get().get_player(i)->change_z(delta);
		}
	}
}

void World::lower_tile(Point3f location)	{
	Tile* ti = get_tile(location);
	float delta = Game_Model::get().get_time_step() * Tile_Move_Speed;
	if(ti->set_height(-delta))	{
		for(int i = 0; i < 4; i++)	{
			if(get_tile(Game_Model::get().get_player(i)->get_posistion()) == ti)
				Game_Model::get().get_player(i)->change_z(-delta);
		}
	}
}

float World::get_friction_coeff(Point3f &spot)	{
	Tile *t = get_tile(spot);
	switch(t->get_covering())	{
	case SOFT_SNOW:
	case HARD_SNOW:
		return Norml_friction;
	case ICE:
		return Ice_friction;
	default:
		return Norml_friction;
	}
}

bool World::allowed_to_scoop(Point3f &pos_)	{
	Tile *t = get_tile(pos_);
	switch(t->get_covering())	{
	case SOFT_SNOW:
		return true;
	case HARD_SNOW:
	case ICE:
	default:
		return false;
		break;
	}
}


/* returns height of ground at that location*/
float World::get_ground_height(Zeni::Point3f location)
{
	return get_tile(location)->get_height();

}

bool World::is_boundary_tile(Tile* t)	{
	if(t->get_col() == 0 || t->get_col() == map_width - 1	
		|| t->get_row() == 0 || t->get_row() == map_height - 1)
		return true;
	return false;
}
