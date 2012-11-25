#include "Seen_Object.h"

#include <zenilib.h>

using namespace Zeni;

Seen_Object::Seen_Object(const Zeni::Point3f &center_,
              const Zeni::Vector3f &size_,
              const Zeni::Quaternion &theta_ 
			  )	:
center(center_), size(size_), rotation(theta_)
{

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

bool Seen_Object::is_on_ground()	{
	//return true if Object is on the ground
	if(center.z <= 5 && center.z)
		return true;
	return false;
}

bool Seen_Object::is_alive()	{
	return alive;
}
