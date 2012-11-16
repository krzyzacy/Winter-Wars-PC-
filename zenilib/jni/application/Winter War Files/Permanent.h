#pragma once
#include "Collidable.h"
#include "Seen_Object.h"

class Permanent :
	public Collidable, public Seen_Object
{
public:
	Permanent(void);
	~Permanent(void);

	
	const model_key_t get_model_name() const
		{return "world";}
};

