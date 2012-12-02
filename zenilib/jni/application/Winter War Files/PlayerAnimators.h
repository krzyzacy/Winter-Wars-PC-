#pragma once

#include "PlayerAnimator.h"

#include "Seen_Object.h"

class Walking : public PlayerAnimator
{	
public:
	/* choose the frame to currently render and set it */
	void animate(Zeni::Model *);

	/* get the next state based on what event happened */
	PlayerAnimator *get_next(PlayerEvent_e);
	
	/* return the model key */
	model_key_t get_model_name();

private:
	int curFrame;
};


class Standing : public PlayerAnimator
{	
public:
	/* choose the frame to currently render and set it */
	void animate(Zeni::Model *);

	/* get the next state based on what event happened */
	PlayerAnimator *get_next(PlayerEvent_e);
	
	/* return the model key */
	model_key_t get_model_name();
};