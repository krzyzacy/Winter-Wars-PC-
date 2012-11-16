#pragma once

/*
	RENDERABLE

A Seen_Object object is an object that can be 
	rendered by translating, scaling, 
	and rotating some 3D Model.  
*/

#include <zenilib.h>
#include <string>

typedef std::string model_key_t;

class Seen_Object
{
public:
	Seen_Object(const Zeni::Point3f &position_ = Zeni::Point3f(0,0,0),
              const Zeni::Vector3f &size_ = Zeni::Vector3f(1,1,1),
              const Zeni::Quaternion &theta_ 
				= Zeni::Quaternion::Axis_Angle(Zeni::Vector3f(0.0f, 0.0f, 1.0f), 0.0f));

	virtual ~Seen_Object(void) = 0;

	void render(Zeni::Model *model) const;

	virtual const model_key_t get_model_name() const = 0;


protected:
	Zeni::Point3f center;
	Zeni::Vector3f size;
    Zeni::Quaternion rotation;

};

