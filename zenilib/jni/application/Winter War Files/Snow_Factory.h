#pragma once
#include "Structure.h"

class Snow_Factory : public Structure
{
public:
	Snow_Factory(Team *team, Tile* tile_,
				const Zeni::Point3f &base_);
	~Snow_Factory(void);

	void update(const float&);
	
	virtual Structure_Type get_type()
	{ return SNOW_FACTORY;}

	const model_key_t get_model_name() const;

	bool is_snow_maker()	{return true;}

	Animator* get_animator();

	void set_proper_dimensions_and_position();

private:

	Animator *get_animator() const;
	
	void create_body();
};