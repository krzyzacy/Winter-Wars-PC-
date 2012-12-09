#include "Effect.h"
#include "Seen_Object.h"

#include <zenilib.h>

using namespace Zeni;


Effect::Effect(const std::string &name_, const Point3f &position_,
              const Vector3f &size_) :
	Seen_Object(position_, size_), name(name_)	
{
}
	

const model_key_t Effect::get_model_name() const
{
	return name;
}

