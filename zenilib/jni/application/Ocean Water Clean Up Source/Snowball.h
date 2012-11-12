#pragma once
#include "game_object.h"

#include "zenilib.h"

class Player;
class Collision_Table;

class Snowball : public Game_Object
{
public:
	Snowball(float size_, Player *p);
	~Snowball(void);

	Zeni::Model *get_m() const
		{return model;}

	virtual int get_ID() const 
		{return snowball_ID_c;}
	
	void update();
	void render() const;

	void get_thrown(Zeni::Point3f pos, Zeni::Vector3f dir);

protected:
	virtual int get_parent_ID() const
		{return Game_Object::get_ID();}

private:
	static Zeni::Model *model;
    static unsigned long m_instance_count;
	const static int snowball_ID_c;
	
	friend Collision_Table;

	int multiplier;
	bool in_air;
	Player *owner;
};

