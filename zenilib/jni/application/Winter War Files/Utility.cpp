
#include "Utility.h"
#include <zenilib.h>
#include <cmath>

//temp

using namespace Zeni;

Zeni::String Structure_Names[NUM_STRUCTURES] = {"Nothing", 
	"Snowman", "Fort", "Snow Factory", "Healing Pool", "Tree", "Base"};

void scaled_render_text(const Zeni::String text, const Zeni::Point3f &position, const Zeni::Color &color, float range){
	float ratio = 1.0f;
	float msglength = get_Fonts()["system_36_800x600"].get_text_width(text);

	while(msglength > range){
		msglength *= 0.9f;
		ratio *= 0.9f;
	}

	get_Fonts()["system_36_800x600"].render_text(text ,position, Vector3f(ratio,0,0), Vector3f(0,ratio,0), color);
}

void scaled_render_text_height(const Zeni::String text, const Zeni::Point3f &position, const Zeni::Color &color, float height)
{
	float ratio = 1.0f;
	float msgheight = get_Fonts()["system_36_800x600"].get_text_height();

	while(msgheight > height){
		msgheight *= 0.9f;
		ratio *= 0.9f;
	}

	get_Fonts()["system_36_800x600"].render_text(text ,position, Vector3f(ratio,0,0), Vector3f(0,ratio,0), color);
}

Zeni::String make_time_string(int seconds)
{
	Zeni::String time_string = itoa(seconds / 60) + ":" ;

	if(seconds % 60 < 10)
		time_string += "0";
	 
	time_string += itoa(seconds % 60);
	return time_string;
}