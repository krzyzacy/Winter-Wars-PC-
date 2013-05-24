#pragma once

#include <zenilib.h>
#include <string>

class Player;

class Player_View
{
public:
	Player_View(const Player *);

	virtual ~Player_View() = 0;

	void set_camera(const Zeni::Point2f &topLeft, const Zeni::Point2f &bottomRight);

	virtual void render_hud(const Zeni::Point2f &topLeft, const Zeni::Point2f &bottomRight);

	virtual void render_minimap(const Zeni::Point2f &topLeft, const Zeni::Point2f &bottomRight, const std::string avatar);

	void render_build(const Zeni::Point2f &topLeft, const Zeni::Point2f &bottomRight);

	void render_death(const Zeni::Point2f &topLeft, const Zeni::Point2f &bottomRight);

	void render_message(const Zeni::Point2f &topLeft, const Zeni::Point2f &bottomRight, const Zeni::String message);

	void render_tree_claimed(const Zeni::Point2f &topLeft, const Zeni::Point2f &bottomRight);

	const virtual Player *get_player() const 
		{return player;}

	const virtual std::string get_avatar();

private:
	const Player *player;

};
