#pragma once

#include "Seen_Object.h"

class Animator;
class EffectAnimator;

class Effect : public Seen_Object
{
public:
	Effect(const std::string &model_, const Zeni::Point3f &position_ = Zeni::Point3f(0,0,0),
              const Zeni::Vector3f &size_ = Zeni::Vector3f(10,10,10), int frame_death_ = 20);
	
	~Effect();
	
	virtual const model_key_t get_model_name() const;
	
	Animator *get_animator() const;
private:
	int frame_death;
	std::string name;
	EffectAnimator *effect_state;
};


