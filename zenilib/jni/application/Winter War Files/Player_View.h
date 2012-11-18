#pragma once

#include <zenilib.h>

class Player;

class Player_View
{
public:
	Player_View(const Player *);

	~Player_View();

	void set_camera(const Zeni::Point2f &topLeft, const Zeni::Point2f &bottomRight);

	void render_hud();

private:
	const Player *player;

};


