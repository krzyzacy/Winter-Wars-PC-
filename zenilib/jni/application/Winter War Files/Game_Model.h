#pragma once

class View;

class Game_Model
{
public:
	Game_Model(void);
	~Game_Model(void);

	void update();

	View *get_View()
		{return view;}

private:
	View *view;

};

