#pragma once

class Collision_Table;

class Collidable
{
public:
	virtual int get_ID() const
		{return collidable_ID_c;}

	Collidable(void);
	virtual ~Collidable(void);

	virtual void update(const float &) = 0;

private:
	virtual void create_body() {}
	
	// Collison Stuff
	const static int collidable_ID_c;
	friend Collision_Table;
};

