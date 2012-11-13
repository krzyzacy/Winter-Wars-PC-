#include "Renderable.h"

#include <zenilib.h>
//#include "Utility.h"


Renderable::Renderable(void)
{
}


Renderable::~Renderable(void)
{
}

void Renderable::render(Zeni::Model *model) const
{
//	if (!model)
//		throw Error("Trying to render NULL Model!");

	const std::pair<Zeni::Vector3f, float> rotation = rotation.get_rotation();

    model->set_translate(center);
    model->set_scale(size);
    model->set_rotate(rotation.second, rotation.first);

    model->render();
}