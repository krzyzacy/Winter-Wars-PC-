#pragma once
#include "Structure.h"

class Snowman : public Structure
{
public:
	Snowman(Team *team,
			const Zeni::Point3f &position_);
	~Snowman(void);

	void update(const float&);

	const model_key_t get_model_name() const;

private:
	// Stuff?

};

