#pragma once

#include "Seen_Object.h"

class Animator
{
public:
	/* choose the frame to currently render and set it */
	virtual void animate(Zeni::Model *) = 0;

	/* return the model key */
	virtual model_key_t get_model_name() = 0;
};
