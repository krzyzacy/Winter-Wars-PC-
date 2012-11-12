#pragma once

#include <vector>
#include <zenilib.h>


enum Floor {SNOW, PACKABLE};

struct Tile
{
	Floor floor;
	int height;
};

class World
{
public:
	World(void);
	~World(void);

	int get_z(int x, int y) ;

	void render() const;

private:
	std::vector<std::vector<Tile>> map;
	Zeni::Model *model;

};

