#include "Target.h"

#include <zenilib.h>

#include "Game_Model.h"

using namespace Zeni;

const int Target::target_ID_c = 3;
unsigned long Target::m_instance_count = 0;
Model *Target::model;

Target::Target(const Vector3f &pos, float size, int p)
	: Game_Object(pos, Vector3f(1,1,1)*size, 3)
	, points(p)
{
    if(!m_instance_count)
      model = new Model("models/target.3ds");
    ++m_instance_count;

}

Target::~Target(void)
{
    if(!--m_instance_count) {
      delete model;
      model = 0lu;
    }
}

void Target::update()
{
	float speed = .25 * (Game_Model::get().difficulty-1);

	m_velo = Vector3f(0,0, speed);
	Game_Object::update();
}

void Target::render() const
{
	Game_Object::render();	
}
