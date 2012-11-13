#pragma once

#include <zenilib.h>


class Renderable
{
public:
	Renderable(void);
	~Renderable(void);

	void render();

protected:
	Zeni::Point3f center;
	Zeni::Vector3f size;
	Zeni::Vector3f orientation;

private:

		
};

