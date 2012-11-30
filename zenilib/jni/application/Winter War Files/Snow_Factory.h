#pragma once
#include "Structure.h"

class Snow_Factory : public Structure
{
public:
	Snow_Factory(Team *team,
			const Zeni::Point3f &position_);
	~Snow_Factory(void);

	void update(const float&);

	const model_key_t get_model_name() const;

private:
	// Stuff?

};