#include "Controls.h"


Controls::Controls(bool inverted_)
{
}


Controls::~Controls(void)
{
}

void Controls::clear_direction()	{
	input.right_x = 0;
	input.right_y = 0;
	input.left_x = 0;
	input.left_y = 0;

}

