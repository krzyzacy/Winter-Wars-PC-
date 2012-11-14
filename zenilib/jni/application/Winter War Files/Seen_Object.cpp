#include "Seen_Object.h"

#include <zenilib.h>

using namespace Zeni;

Seen_Object::Seen_Object(void)
{
	center = Point3f(100,100,100);
	size = Vector3f(1,1,1);
}


Seen_Object::~Seen_Object(void)
{
}

void Seen_Object::render(Model *model) const
{
	if (!model)
		throw Error("Trying to render NULL Model!");

	const std::pair<Vector3f, float> rot = rotation.get_rotation();

    model->set_translate(center);
    model->set_scale(size);
    model->set_rotate(rot.second, rot.first);

    model->render();
}