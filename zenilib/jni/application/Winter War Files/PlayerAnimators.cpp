

#include "PlayerAnimators.h"

// WALKING
void Walking::animate(Zeni::Model *model)
{
	//model->set_keyframe(curFrame++);
}

PlayerAnimator *Walking::get_next(PlayerEvent_e pevent)
{
	switch (pevent)
	{
		case MOVE:
			return NULL;
			break;
	}
}
	
model_key_t Walking::get_model_name()
{
	return "player";
}


// STANDING
void Standing::animate(Zeni::Model *model)
{

}

PlayerAnimator *Standing::get_next(PlayerEvent_e pevent)
{
	switch (pevent)
	{
		case MOVE:
			return new Walking();
			break;
	}
}
	
model_key_t Standing::get_model_name()
{
	return "player";
}