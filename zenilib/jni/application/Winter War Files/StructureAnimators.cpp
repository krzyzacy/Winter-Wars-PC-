#include "Game_Model.h"
#include "StructureAnimators.h"

/*---------------------------------------------
				FORTRESS
---------------------------------------------*/

void Fort_spin::animate(Zeni::Model *model)
{
	FSFrame += Game_Model::get().get_time_step()*4*10;
	Frame = FSFrame;
	Frame = (Frame % 50) + 1;
	model->set_keyframe(Frame);
}

StructureAnimator *Fort_spin::get_next(StructureEvent_e sevent)
{
	switch (sevent)
	{
		case FORT_SPIN:
			return NULL;
			break;
		case FORT_ISO:
			return new Fort_isolated();
			break;
		default:
			return NULL;
			break;
	}
}
	
model_key_t Fort_spin::get_model_name()
{
	return "fortress_spin";
}

void Fort_isolated::animate(Zeni::Model *model)
{
	FIFrame += Game_Model::get().get_time_step()*4*10;
	Frame = FIFrame;
	Frame = (Frame % 50) + 1;
	model->set_keyframe(Frame);
}

StructureAnimator *Fort_isolated::get_next(StructureEvent_e sevent)
{
	switch (sevent)
	{
		case FORT_SPIN:
			return new Fort_spin();
			break;
		case FORT_ISO:
			return NULL;
			break;
		default:
			return NULL;
			break;
	}
}
	
model_key_t Fort_isolated::get_model_name()
{
	return "fortress_isolated";
}


/*---------------------------------------------
				SNOWMAN
---------------------------------------------*/

void Snowman_stand::animate(Zeni::Model *model)
{
	SMFrame += Game_Model::get().get_time_step()*4*10;
	Frame = SMFrame;
	Frame = (Frame % 50) + 1;
	model->set_keyframe(Frame);
}

StructureAnimator *Snowman_stand::get_next(StructureEvent_e sevent)
{
	switch (sevent)
	{
		case SM_STAND:
			return NULL;
			break;
		case SM_THROWL:
			return new Snowman_thwl();
			break;
		case SM_THROWR:
			return new Snowman_thwr();
			break;
		case SM_ISO:
			return new Snowman_isolated();
			break;
		default:
			return NULL;
			break;
	}
}
	
model_key_t Snowman_stand::get_model_name()
{
	return "snowman_stand";
}

void Snowman_thwr::animate(Zeni::Model *model)
{
	SMFrame += Game_Model::get().get_time_step()*4*20;
	if (SMFrame >= 50) finished = true;
	Frame = SMFrame;
	Frame = (Frame % 50) + 1;
	model->set_keyframe(Frame);
}

StructureAnimator *Snowman_thwr::get_next(StructureEvent_e sevent)
{
	if (finished)
		{
		switch (sevent)
			{
			case SM_STAND:
				return new Snowman_stand();
				break;
			case SM_THROWR:
				return new Snowman_thwr();
				break;
			case SM_ISO:
				return new Snowman_isolated();
				break;
			default:
				return NULL;
				break;
			}
		}
	else
		{
		switch (sevent)
			{
			case SM_THROWL:
				return new Snowman_thwl();
				break;
			case SM_ISO:
				return new Snowman_isolated();
				break;
			default:
				return NULL;
				break;
			}
		}
}
	
model_key_t Snowman_thwr::get_model_name()
{
	return "snowman_throw_right";
}

void Snowman_thwl::animate(Zeni::Model *model)
{
	SMFrame += Game_Model::get().get_time_step()*4*20;
	if (SMFrame >= 50) finished = true;
	Frame = SMFrame;
	Frame = (Frame % 50) + 1;
	model->set_keyframe(Frame);
}

StructureAnimator *Snowman_thwl::get_next(StructureEvent_e sevent)
{
	if (finished)
		{
		switch (sevent)
			{
			case SM_STAND:
				return new Snowman_stand();
				break;
			case SM_THROWR:
				return new Snowman_thwr();
				break;
			case SM_ISO:
				return new Snowman_isolated();
				break;
			default:
				return NULL;
				break;
			}
		}
	else
		{
		switch (sevent)
			{
			case SM_THROWR:
				return new Snowman_thwr();
				break;
			case SM_ISO:
				return new Snowman_isolated();
				break;
			default:
				return NULL;
				break;
			}
		}
}
	
model_key_t Snowman_thwl::get_model_name()
{
	return "snowman_throw_left";
}

void Snowman_isolated::animate(Zeni::Model *model)
{
	SIFrame += Game_Model::get().get_time_step()*4*20;
	Frame = SIFrame;
	Frame = (Frame % 50) + 1;
	model->set_keyframe(Frame);
}

StructureAnimator *Snowman_isolated::get_next(StructureEvent_e sevent)
{
	switch (sevent)
	{
		case SM_STAND:
			return new Snowman_stand();
			break;
		case SM_THROWL:
			return new Snowman_thwl();
			break;
		case SM_THROWR:
			return new Snowman_thwr();
			break;
		case SM_ISO:
			return NULL;
			break;
		default:
			return NULL;
			break;
	}
}

model_key_t Snowman_isolated::get_model_name()
{
	return "snowman_isolated";
}

/*---------------------------------------------
				FACTORY
---------------------------------------------*/

void Factory_spin::animate(Zeni::Model *model)
{
	FSFrame += Game_Model::get().get_time_step()*4*4;
	Frame = FSFrame;
	Frame = (Frame % 50) + 1;
	model->set_keyframe(Frame);
}

StructureAnimator *Factory_spin::get_next(StructureEvent_e sevent)
{
	switch (sevent)
	{
		case FAC_SPIN:
			return NULL;
			break;
		case FAC_ISO:
			return new Factory_isolated();
			break;
		default:
			return NULL;
			break;
	}
}
	
model_key_t Factory_spin::get_model_name()
{
	return "factory_spin";
}

void Factory_isolated::animate(Zeni::Model *model)
{
	FIFrame += Game_Model::get().get_time_step()*4*4;
	Frame = FIFrame;
	Frame = (Frame % 50) + 1;
	model->set_keyframe(Frame);
}

StructureAnimator *Factory_isolated::get_next(StructureEvent_e sevent)
{
	switch (sevent)
	{
		case FAC_SPIN:
			return new Factory_spin();
			break;
		case FAC_ISO:
			return NULL;
			break;
		default:
			return NULL;
			break;
	}
}
	
model_key_t Factory_isolated::get_model_name()
{
	return "factory_isolated";
}

/*---------------------------------------------
				HEALING POOL
---------------------------------------------*/

void Pool_heal::animate(Zeni::Model *model)
{
	PHFrame += Game_Model::get().get_time_step()*4*5;
	Frame = PHFrame;
	Frame = (Frame % 50) + 1;
	model->set_keyframe(Frame);
}

StructureAnimator *Pool_heal::get_next(StructureEvent_e sevent)
{
	switch (sevent)
	{
		case POOL_ISO:
			return new Pool_isolated();
			break;
		case POOL_HEAL:
			return NULL;
			break;
		default:
			return NULL;
			break;
	}
}
	
model_key_t Pool_heal::get_model_name()
{
	return "healing_pool_heal";
}

void Pool_isolated::animate(Zeni::Model *model)
{
	PIFrame += Game_Model::get().get_time_step()*4*5;
	Frame = PIFrame;
	Frame = (Frame % 50) + 1;
	model->set_keyframe(Frame);
}

StructureAnimator *Pool_isolated::get_next(StructureEvent_e sevent)
{
	switch (sevent)
	{
		case POOL_ISO:
			return NULL;
			break;
		case POOL_HEAL:
			return new Pool_heal();
			break;
		default:
			return NULL;
			break;
	}
}
	
model_key_t Pool_isolated::get_model_name()
{
	return "healing_pool_isolated";
}

/*---------------------------------------------
				PRESENTS
---------------------------------------------*/

void Present_wrapped::animate(Zeni::Model *model)
{
	PWFrame += Game_Model::get().get_time_step()*4*10;
	Frame = PWFrame;
	Frame = (Frame % 50) + 1;
	model->set_keyframe(Frame);
}

StructureAnimator *Present_wrapped::get_next(StructureEvent_e sevent)
{
	switch (sevent)
	{
		case FORT_SPIN:
			return new Fort_spin();
			break;
		case FORT_ISO:
			return new Fort_isolated();
			break;
		case SM_STAND:
			return new Snowman_stand();
			break;
		case SM_THROWL:
			return new Snowman_thwl();
			break;
		case SM_THROWR:
			return new Snowman_thwr();
			break;
		case SM_ISO:
			return new Snowman_isolated();
			break;
		case FAC_SPIN:
			return new Factory_spin();
			break;
		case FAC_ISO:
			return new Factory_isolated();
			break;
		case POOL_ISO:
			return new Pool_isolated();
			break;
		case POOL_HEAL:
			return new Pool_heal();
			break;
		case PRESENT_WRAP:
			return NULL;
			break;
		default:
			return NULL;
			break;
	}
}
	
model_key_t Present_wrapped::get_model_name()
{
	return "present_wrapped";
}

void Present_unwrapped::animate(Zeni::Model *model)
{
	PUFrame += Game_Model::get().get_time_step()*4*10;
	Frame = PUFrame;
	Frame = (Frame % 50) + 1;
	model->set_keyframe(Frame);
}

StructureAnimator *Present_unwrapped::get_next(StructureEvent_e sevent)
{
	switch (sevent)
	{
		case PRESENT_WRAP:
			return new Present_wrapped();
			break;
		case PRESENT_UNWRAP:
			return NULL;
			break;
		default:
			return NULL;
			break;
	}
}
	
model_key_t Present_unwrapped::get_model_name()
{
	return "present_unwrapped";
}

/*---------------------------------------------
				TREE
---------------------------------------------*/

void Tree_owned::animate(Zeni::Model *model)
{
	TOFrame += Game_Model::get().get_time_step()*4*10;
	Frame = TOFrame;
	Frame = (Frame % 50) + 1;
	model->set_keyframe(Frame);
}

//enum StructureEvent_e{FORT, SM_STAND, SM_THROWL, SM_THROWR, FAC_SPIN, POOL_STAND, POOL_HEAL, TREE_OWNED, TREE_UNOWNED, PRESENT_WRAP, PRESENT_UNWRAP};

StructureAnimator *Tree_owned::get_next(StructureEvent_e sevent)
{
	switch (sevent)
	{
		case TREE_OWNED:
			return NULL;
			break;
		case TREE_UNOWNED:
			return new Tree_owned();
			break;
		default:
			return NULL;
			break;
	}
}
	
model_key_t Tree_owned::get_model_name()
{
	return "tree_owned";
}

void Tree_unowned::animate(Zeni::Model *model)
{
	TUFrame += Game_Model::get().get_time_step()*4*10;
	Frame = TUFrame;
	Frame = (Frame % 50) + 1;
	model->set_keyframe(Frame);
}

StructureAnimator *Tree_unowned::get_next(StructureEvent_e sevent)
{
	switch (sevent)
	{
		case TREE_OWNED:
			return new Tree_unowned();
			break;
		case TREE_UNOWNED:
			return NULL;
			break;
		default:
			return NULL;
			break;
	}
}
	
model_key_t Tree_unowned::get_model_name()
{
	return "tree_unowned";
}