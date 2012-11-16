#pragma once
#include "Collidable.h"
#include "Seen_Object.h"

class Permanent :
	public Collidable, public Seen_Object
{
public:
	Permanent(const Zeni::Point3f &position_ = Zeni::Point3f(0,0,0),
              const Zeni::Vector3f &size_ = Zeni::Vector3f(1,1,1),
              const Zeni::Quaternion &theta_ 
				= Zeni::Quaternion::Axis_Angle(Zeni::Vector3f(0.0f, 0.0f, 1.0f), 0.0f));
	~Permanent(void);

	
	const model_key_t get_model_name() const
		{return "world";}
};

