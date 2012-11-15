#pragma once

class View;

class Game_Model
{
public:
	Game_Model(void);
	~Game_Model(void);


	View *get_View();

private:
	View *view;
};

