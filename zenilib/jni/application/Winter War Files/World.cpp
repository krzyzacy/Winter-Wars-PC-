#include "World.h"

#include "Game_Model.h"
#include "View.h"
#include "Tile.h"

using namespace std;

World::World( View *view_,
		const int width__,
		const int height__,
		const float hex_length__
		) :
	map(height__, vector<Tile *>(width__, 0) ),
	view(view_)
{



	tile_size = hex_length__;

	float tR = sqrt(3.0f) * tile_size / 2;
	float tS = tile_size;
	float tH = tile_size / 2; 

	for(int h = 0; h < height__; h++){
		for(int w = 0; w < width__; w++){

			Zeni::Point3f center;
			center.x = w * tR * 2 + tR;
			if(h % 2 == 1) center.x += tR;
			
			center.y = h * (tH + tS) + tS;
			center.z = - 60.0f;
			if(h == 0 || h == height__-1 || w == 0 || w == width__-1)
				center.z = 10.0f;
			
			float scale_size = 2.0*tile_size;
			Tile* tmp;
			tmp = new Tile(center,Zeni::Vector3f(scale_size,scale_size,scale_size),w,h);

			int randomteam = rand() % 5;
			int randomcover = rand() % 3;

			if(randomteam == 0) tmp->set_team(NEUTRAL);
			if(randomteam == 1) tmp->set_team(GREEN);
			if(randomteam == 2) tmp->set_team(RED);
			if(randomteam == 3) tmp->set_team(BLUE);
			if(randomteam == 4) tmp->set_team(ORANGE);

			if(randomcover == 0) tmp->set_covering(SOFT_SNOW);
			if(randomcover == 1) tmp->set_covering(HARD_SNOW);
			if(randomcover == 2) tmp->set_covering(ICE);
			
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

	float tR = sqrt(3.0f) * tile_size / 2;
	float tS = tile_size;
	float tH = tile_size / 2; 

	// "slice" the map as squares - type A and type B
	// and adjust the vector index accordingly
	
	int sec_x = xr / (2 * tR);
	int sec_y = yr / (tS + tH);

	xr -= sec_x * 2 * tR;
	yr -= sec_y * (tS + tH);

	if(sec_y % 2 == 0){ // odd row, section A
		if(yr >= tH)
			return map[sec_y][sec_x];
		else if(xr >= tR){
			if(yr <= (sqrt(3.0f) / 3 ) * (xr - tR) ){
				if(sec_y != 0)
					return map[sec_y - 1][sec_x];
				else
					return NULL;
					//cerr << "not a valid coordination" << endl;
					
			}
			else
				return map[sec_y][sec_x];
		}
		else{
			if(yr <= (-(sqrt(3.0f) * xr)/3 + tH)){
				if(sec_y != 0 && sec_x != 0)
					return map[sec_y - 1][sec_x - 1];
				else
					return NULL;
					//cerr << "not a valid coordination" << endl;
			}
			else
				return map[sec_y][sec_x];
		}
	}
	else{ // even row, section B
		if(xr >= tR){
			if(yr >= tH)
				return map[sec_y][sec_x];
			else{
				if(yr <= (-(sqrt(3.0f) * (xr - tR))/3 + tH)){
					if(sec_y != 0)
						return map[sec_y - 1][sec_x];
					else
						return NULL;
						//cerr << "not a valid coordination" << endl;
				}
				else
					return map[sec_y][sec_x];
			}
		}
		else{
			if(yr >= tH){
				if(sec_x != 0)
					return map[sec_y][sec_x - 1];
				else
					return NULL;
					//cerr << "not a valid coordination" << endl;
			}
			else{
				if(yr <= (sqrt(3.0f) / 3 ) * xr ){
					if(sec_x != 0)
						return map[sec_y - 1][sec_x];
					else
						return NULL;
						//cerr << "not a valid coordination" << endl;
				}
				else{
					if(sec_y != 0)
						return map[sec_y][sec_x - 1];
					else
						return NULL;
						//cerr << "not a valid coordination" << endl;
				}
			}
		}
	}
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

//&&& Sen if you could make this give the corners, in some sort of order that'd be cool
Tile * World::get_next_Base_Tile()	{
	return 0;
}

