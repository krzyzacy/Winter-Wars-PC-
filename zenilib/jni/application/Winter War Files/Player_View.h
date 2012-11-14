
class Player;

class Player_View
{
public:
	Player_View(const Player *);

	~Player_View();

	void set_camera();

	void render_hud();

private:
	const Player *player;

};