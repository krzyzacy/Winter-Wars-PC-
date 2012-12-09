#pragma once

#include "Animator.h"

enum StructureEvent_e{FORT_SPIN, SM_STAND, SM_THROWL, SM_THROWR, FAC_SPIN, POOL_STAND, POOL_HEAL, TREE_OWNED, TREE_UNOWNED, PRESENT_WRAP, PRESENT_UNWRAP};

class StructureAnimator : public Animator
{
public:
	/* choose the frame to currently render and set it */
	virtual void animate(Zeni::Model *) = 0;

	/* get the next state based on what event happened */
	virtual StructureAnimator *get_next(StructureEvent_e) = 0;

	/* return the model key */
	virtual model_key_t get_model_name() = 0;

};