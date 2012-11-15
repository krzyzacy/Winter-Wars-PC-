#pragma once
#include "Seen_Object.h"

class Collidable :
	public Seen_Object
{
public:
	Collidable(void);
	virtual ~Collidable(void);

	const model_key_t get_model_name() const
		{return "snowball";}
};

