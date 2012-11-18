#pragma once

class View;
class World;

class Game_Model
{
public:
	static Game_Model &get()
	{
		static Game_Model m;
		return m;
	}
	
	~Game_Model(void);

	void update();

	View *get_View()
		{return view;}

private:
	Game_Model(void);
	View *view;
	World *world;

};

