#pragma once
#include "Structure.h"

class Healing_Pool : public Structure
{
public:
	Healing_Pool(Team *team,
			const Zeni::Point3f &position_);
	~Healing_Pool(void);

	void update(const float&);

	const model_key_t get_model_name() const;

private:
	// Stuff?

};