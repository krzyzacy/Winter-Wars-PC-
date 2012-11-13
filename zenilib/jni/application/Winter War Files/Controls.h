#pragma once

class Controls
{
public:
	Controls(bool inverted = false);
	~Controls(void);

	void take_input();

	void pass_actions();

private:
	// Each of the following should coorespond to a player action
	bool left;
	bool forward; 
	bool turn;		// left-right camera
	bool pitch;		// up-down camera
	bool fire;
};

