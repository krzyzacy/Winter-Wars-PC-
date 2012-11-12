#pragma once
#include "game_object.h"

#include "zenilib.h"

class Collision_Table;

class Target : public Game_Object
{
public:
	Target(const Zeni::Vector3f &pos, float size, int points_worth);
	~Target(void);

	Zeni::Model *get_m() const
		{return model;}

	virtual int get_ID() const 
		{return target_ID_c;}

	int get_points(){
		return points;}
	
	void update();
	void render() const;

protected:
	virtual int get_parent_ID() const
		{return Game_Object::get_ID();}

private:
	static Zeni::Model *model;
    static unsigned long m_instance_count;
	const static int target_ID_c;
	friend Collision_Table;

	int points;

};

