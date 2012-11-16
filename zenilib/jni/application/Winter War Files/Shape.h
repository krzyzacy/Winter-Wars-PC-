#pragma once

#include <zenilib.h>

class Shape
{
public:
	Shape(void);
	~Shape(void);
	/*
	// adds a shape to this shape.  
	// throws Error if can't (component)
	virtual void add_Shape(Shape *);

	// changes the shape by creating new shapes
	virtual void change(const Zeni::Point3f &center
						, const Zeni::Vector3f &distance_to_corner
						, const Zeni::Quaternion);

	// !!OR!! ONLY IMPLEMENT CHANGE OR THE THREE BELOW INSIDE DERIVED CLASSES!!!

	// moves the shapes
	virtual void translate(const Zeni::Vector3f &);	
	virtual void scale(const Zeni::Vector3f &factor);
	virtual void rotate(const Zeni::Quaternion&); //or whatever makes sense here
	*/
};

