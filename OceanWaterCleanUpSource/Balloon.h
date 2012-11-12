#pragma once

#include "game_object.h"
#include "Multiplier.h"

#include <vector>
#include <zenilib.h>

class Collision_Table;

class Balloon :
	public Game_Object
{
public:
	Balloon(const Zeni::Point2f &position_,
			const Zeni::Vector2f &size_,
			int area_,
			int worth_,
			const Zeni::String &image_) 
	:  Game_Object(position_, size_, 1.0f)
		, area(area_), worth(worth_), image(image_)
	{}
	
	~Balloon(void);

	void render() const;

	void update();

	virtual int get_ID() const 
		{return balloon_ID_c;}

	void pass(Balloon &B, const Zeni::Point2f &);
	void get_hit(Player *p)
		{
			Zeni::play_sound("bounce");
			multipliers.push_back(new Multiplier(p));
		}
	
protected:
	
	void check_walls();
	virtual int get_parent_ID() const 
	{return Game_Object::get_ID();}

private:
	int worth;
	int area;
	Zeni::String image;

	std::vector<Multiplier*> multipliers;

	void remove_multipliers();
	
const static int balloon_ID_c;

friend Collision_Table;
};

