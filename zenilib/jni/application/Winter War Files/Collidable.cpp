#include "Collidable.h"

const int Collidable::collidable_ID_c = 0;

Collidable::Collidable(void)
{
}

Collidable::~Collidable(void)
{
}

void Collidable::update(const float&)
{
	create_body();
}