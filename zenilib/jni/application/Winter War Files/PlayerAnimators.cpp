

#include "Game_Model.h"
#include "PlayerAnimators.h"

// WALKING
void Walking::animate(Zeni::Model *model)
{
	WalkFrame += Game_Model::get().get_time_step()*10;
	Frame = WalkFrame;
	Frame = (Frame % 50) + 1;
	model->set_keyframe(Frame);
}


PlayerAnimator * Walking::get_next(PlayerEvent_e pevent)
{
	switch (pevent)
	{
		case WALK:
			return NULL;
			break;
		case JUMP:
			return NULL;
			break;
		case THROW:
			return NULL;
			break;
		case PACK:
			return NULL;
			break;
		case STAND:
			return new Standing();
			break;
		case SCOOP:
			return NULL;
			break;
		case DIE:
			return NULL;
			break;
		default:
			break;
	}
}
	
model_key_t Walking::get_model_name()
{
	return "player_walk";
}


// STANDING
void Standing::animate(Zeni::Model *model)
{

}

PlayerAnimator *Standing::get_next(PlayerEvent_e pevent)
{
	switch (pevent)
	{
		case WALK:
			return new Walking();
			break;
		case JUMP:
			return NULL;
			break;
		case THROW:
			return NULL;
			break;
		case PACK:
			return NULL;
			break;
		case STAND:
			return NULL;
			break;
		case SCOOP:
			return NULL;
			break;
		case DIE:
			return NULL;
			break;
		default:
			break;
	}
}
	
model_key_t Standing::get_model_name()
{
	return "player_stand";
}