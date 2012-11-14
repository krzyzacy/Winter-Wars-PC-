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
	Seen_Object(void);
	virtual ~Seen_Object(void) = 0;

	// throws Error if model is null
	void render(Zeni::Model *model) const;

	virtual const model_key_t &get_model_name() const = 0;


protected:
	Zeni::Point3f center;
	Zeni::Vector3f size;
    Zeni::Quaternion rotation;

};

