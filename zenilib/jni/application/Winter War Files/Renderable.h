#pragma once

#include <zenilib.h>
#include <string>

typedef std::string model_key_t;

class Renderable
{
public:
	Renderable(void);
	virtual ~Renderable(void) = 0;

	// throws Error if model is null
	void render(Zeni::Model *model) const;

	const model_key_t &get_model_name() const
		{return model;}

protected:
	Zeni::Point3f center;
	Zeni::Vector3f size;
	Zeni::Vector3f orientation;

private:
	model_key_t model;

};

