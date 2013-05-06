
#ifndef GLOBALS_H
#define GLOBALS_H

#include <zenilib.h>
#include <vector>

class Game_Parameter
{
public:
	Game_Parameter(const Zeni::String &name_, int default_value_, 
				int max_, int unit_increment_ = 10, int min_ = 0)
		: name(name_), unit_increment(unit_increment_), 
		default_value(default_value_), current_value(default_value_),
		max(max_), min(min_)
	{}

	Zeni::String name;

	void increment();
	void decrement();

	int &get_value() {return current_value;}

	void reset();

	Game_Parameter &operator++() {increment(); return *this;}
	Game_Parameter &operator--() {decrement(); return *this;}

private:
	int unit_increment;
	int default_value;
	int &current_value;
	int max;
	int min;
};

class Parameter_List
{
public:
	Parameter_List();

	Game_Parameter &at(int i) {return list.at(i);}

	int size() {return list.size();} 

	void reset_all();

private:
	std::vector<Game_Parameter> list;

} ;

extern Parameter_List parameters;

#endif
