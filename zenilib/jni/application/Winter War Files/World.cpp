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
			center.x = w * tR * 2;
			if(h % 2 == 1) center.x += tR;
			
			center.y = h * (tH + tS) + tS;
			center.z = 0.0f;
			
			float scale_size = 2*tile_size;
			Tile* tmp;
			tmp = new Tile(center,Zeni::Vector3f(scale_size,scale_size,scale_size),w,h);

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
		if(yr > tH)
			return map[sec_y][sec_x];
		else if(xr > tR){
			if(yr > ((- sqrt(3.0f) / 3) * (xr - tR) + tH) ){
				if(sec_y != 0)
					return map[sec_y - 1][sec_x];
				else
					cerr << "not a valid coordination" << endl;
			}
			else
				return map[sec_y][sec_x];
		}
		else{
			if(sqrt(3.0f) * yr > xr){
				if(sec_y != 0 && sec_x != 0)
					return map[sec_y - 1][sec_x - 1];
				else
					cerr << "not a valid coordination" << endl;
			}
		}
	}
	else{ // even row, section B
		if(xr > tR){
			if(yr < tH)
				return map[sec_y][sec_x];
			else{
				if( sqrt(3.0f) * yr > (xr - tR)){
					if(sec_y != 0)
						return map[sec_y - 1][sec_x];
					else
						cerr << "not a valid coordination" << endl;
				}
				else
					return map[sec_y][sec_x];
			}
		}
		else{
			if(yr < tH){
				if(sec_x != 0)
					return map[sec_y][sec_x - 1];
				else
					cerr << "not a valid coordination" << endl;
			}
			else{
				if(yr < (- xr / sqrt(3.0f)) + tH ){
					if(sec_x != 0)
						return map[sec_y][sec_x - 1];
					else
						cerr << "not a valid coordination" << endl;
				}
				else{
					if(sec_y != 0)
						return map[sec_y - 1][sec_x];
					else
						cerr << "not a valid coordination" << endl;
				}
			}
		}
	}
}

