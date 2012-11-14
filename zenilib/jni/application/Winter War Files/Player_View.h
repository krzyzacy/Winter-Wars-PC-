#include <vector>

class Player;

class Player_View
{
public:
	Player_View(const Player *);

	~Player_View();

	void set_camera();

	void render_hud();

private:
	std::vector<Player*> players;

};