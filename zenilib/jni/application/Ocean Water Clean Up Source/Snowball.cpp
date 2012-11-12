#include "Snowball.h"

#include <zenilib.h>

using namespace Zeni;

const int Snowball::snowball_ID_c = 1;
unsigned long Snowball::m_instance_count = 0;
Model *Snowball::model;

Snowball::Snowball(float size_, Player *p)
	: Game_Object(Vector3f(), Vector3f(1,1,1)*size_, size_)
	, in_air(false)
	, owner(p)
	, multiplier(1)
{
    if(!m_instance_count)
      model = new Model("models/soap.3ds");
    ++m_instance_count;

}

Snowball::~Snowball(void)
{
    if(!--m_instance_count) {
      delete model;
      model = 0lu;
    }
}

void Snowball::update()
{
	if (in_air)
	{
		Game_Object::update();
	}
	else
	{
	
	}
}

void Snowball::render() const
{
	if (in_air)
	{
		Game_Object::render();
	}
	else
	{
		
	}
}

void Snowball::get_thrown(Point3f pos, Zeni::Vector3f dir)
{
	in_air = true;

	set_pos(pos);
	accelerate(dir*2);
}