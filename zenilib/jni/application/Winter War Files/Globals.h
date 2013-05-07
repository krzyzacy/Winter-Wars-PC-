
#ifndef GLOBALS_H
#define GLOBALS_H

#include <zenilib.h>
#include <vector>
#include <map>

class Game_Parameter
{
public:
	Game_Parameter(const Zeni::String &name_, float &default_value_, 
				float max_, float unit_increment_ = 10, float min_ = 0)
		: name(name_), unit_increment(unit_increment_), 
		default_value(default_value_), current_value(default_value_),
		max(max_), min(min_)
	{}

	Zeni::String name;

	void increment();
	void decrement();

	float get_value() {return current_value;}
	void set_value(float new_value) { current_value = new_value; }

	void reset();

	Game_Parameter &operator++() {increment(); return *this;}
	Game_Parameter &operator--() {decrement(); return *this;}

private:
	float unit_increment;
	float default_value;
	float &current_value;
	float max;
	float min;
};

class Parameter_List
{
public:
	Parameter_List();

	Game_Parameter &at(int i) {return list.at(i);}
	Game_Parameter &find(const Zeni::String &);

	int size() {return list.size();} 

	void reset_all();

private:
	std::vector<Game_Parameter> list;
	std::map<Zeni::String, int> name_to_index;

} ;

extern Parameter_List parameters;

#endif
