

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
			return new Packing();
			break;
		case STAND:
			return new Standing();
			break;
		case SCOOP:
			return new Scooping();
			break;
		case DIE:
			return new Dying();
			break;
		default:
			return NULL;
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
			return new Packing();
			break;
		case STAND:
			return NULL;
			break;
		case SCOOP:
			return new Scooping();
			break;
		case DIE:
			return new Dying();
			break;
		default:
			return NULL;
			break;
	}
}
	
model_key_t Standing::get_model_name()
{
	return "player_stand";
}

//PACKING
void Packing::animate(Zeni::Model *model)
{
	PackFrame += Game_Model::get().get_time_step()*10;
	Frame = PackFrame;
	Frame = (Frame % 50) + 1;
	model->set_keyframe(Frame);
}


PlayerAnimator * Packing::get_next(PlayerEvent_e pevent)
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
			return new Throwing();
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
			return new Dying();
			break;
		default:
			return NULL;
			break;
	}
}
	
model_key_t Packing::get_model_name()
{
	return "player_pack";
}

//SCOOPING
void Scooping::animate(Zeni::Model *model)
{
	ScoopFrame += Game_Model::get().get_time_step()*10;
	Frame = ScoopFrame;
	Frame = (Frame % 50) + 1;
	model->set_keyframe(Frame);
}

PlayerAnimator * Scooping::get_next(PlayerEvent_e pevent)
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
			return new Packing();
			break;
		case STAND:
			return NULL;
			break;
		case SCOOP:
			return NULL;
			break;
		case DIE:
			return new Dying();
			break;
		default:
			return NULL;
			break;
	}
}
	
model_key_t Scooping::get_model_name()
{
	return "player_scoop";
}

//THROWING
void Throwing::animate(Zeni::Model *model)
{
	ThrowFrame += Game_Model::get().get_time_step()*40;
	Frame = ThrowFrame;

	if (Frame <= 50)
		model->set_keyframe(Frame);
	else
		{
		finished = true;
		model->set_keyframe(50);
		}
}

PlayerAnimator * Throwing::get_next(PlayerEvent_e pevent)
{
	switch (pevent)
	{
		case WALK:
			if (!finished)
				return NULL;
			else
				return new Walking();
			break;
		case JUMP:
			if (!finished)
				return NULL;
			else
				return new Standing();
			break;
		case THROW:
			return NULL;
			break;
		case PACK:
			return NULL;
			break;
		case STAND:
			if (!finished)
				return NULL;
			else
				return new Standing();
			break;
		case SCOOP:
			return NULL;
			break;
		case DIE:
			return new Dying();
			break;
		default:
			return NULL;
			break;
	}
}
	
model_key_t Throwing::get_model_name()
{
	return "player_throw";
}

//DYING
void Dying::animate(Zeni::Model *model)
{
	DieFrame += Game_Model::get().get_time_step()*7.5;
	Frame = DieFrame;
	if (Frame == 50)
		model->set_keyframe(50);
	else
		model->set_keyframe(Frame);
}

PlayerAnimator * Dying::get_next(PlayerEvent_e pevent)
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
			return NULL;
			break;
		case SCOOP:
			return NULL;
			break;
		case DIE:
			return new Dying();
			break;
		default:
			return NULL;
			break;
	}
}
	
model_key_t Dying::get_model_name()
{
	return "player_die";
}