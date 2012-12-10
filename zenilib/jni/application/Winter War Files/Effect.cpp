#include "Effect.h"
#include "Seen_Object.h"

#include "Animator.h"
#include "Game_Model.h"


#include <zenilib.h>

using namespace Zeni;


class EffectAnimator : public Animator
{	
public:
	EffectAnimator(Effect *E_, int frame_death_): frame(0), frame_death(frame_death_), E(E_){}
	void animate(Model *model)
	{
		frame += Game_Model::get().get_time_step()*10;
		int frame_int = frame;

		model->set_keyframe(frame_int++);

		// after enough frames
		if (frame_int > frame_death)
			E->mark_for_deletion();

	}
	
	model_key_t get_model_name()
	{
		return "";
	}


private:
	int frame_death;
	Effect *E;
	float frame;

};


Effect::Effect(const std::string &name_, const Point3f &position_,
              const Vector3f &size_, int frame_death_) :
	Seen_Object(position_, size_), frame_death(frame_death_), name(name_), effect_state(new EffectAnimator(this, frame_death_))	
{
}
	
Effect::~Effect()
{
	delete effect_state;
}

const model_key_t Effect::get_model_name() const
{
	return name;
}



Animator *Effect::get_animator() const
{
	return effect_state;
}

