#pragma once

class Controls
{
public:
	Controls(bool inverted_ = false);
	~Controls(void);

	void take_input();

	void pass_actions();

//private:
	
	struct Inputs	{
		Inputs()	: jump(false), pack(false), mini_map(false), shoot(false), 
			build_view(false), right_y(0.0f), right_x(0.0f), left_y(0.0f), left_x(0.0f)		{}

		bool jump;	//A button
		bool pack;	//B button
		bool mini_map;	//left shoulder
		bool shoot;			//Right trigger
		bool build_view;	//left trigger

		float right_y;	//Right Stick
		float right_x;
		float left_y;		//Left Stick
		float left_x;
	} input;

};

