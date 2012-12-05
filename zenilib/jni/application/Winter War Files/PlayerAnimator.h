#pragma once

#include "Animator.h"

enum PlayerEvent_e{WALK, JUMP, THROW, PACK, STAND, SCOOP, FLINCH, DIE, RESPAWN};

class PlayerAnimator : public Animator
{
public:
	/* choose the frame to currently render and set it */
	virtual void animate(Zeni::Model *) = 0;

	/* get the next state based on what event happened */
	virtual PlayerAnimator *get_next(PlayerEvent_e) = 0;

	/* return the model key */
	virtual model_key_t get_model_name() = 0;

	virtual void proceed() {}

};

