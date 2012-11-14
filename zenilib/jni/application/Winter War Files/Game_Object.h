#pragma once
#include "Seen_Object.h"
class Game_Object :
	public Seen_Object
{
public:
	Game_Object(void);
	virtual ~Game_Object(void);

	const model_key_t get_model_name() const
	{return "snowball";}
};

