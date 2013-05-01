#ifndef __OBJECTIVE_H__
#define __OBJECTIVE_H__

#include <zenilib.h>

class Objective 
{
public:
	Objective();
	virtual ~Objective() = 0;

	virtual bool has_been_completed();
	virtual Zeni::String get_message_to_display();
	virtual Objective* get_next_Objective();

protected:
	Zeni::String message;
};

class Build_a_Healing_Pool : public Objective
{
public:
	Build_a_Healing_Pool()
	{ message = "Build a Healing pool by pressing x!"; }
	~Build_a_Healing_Pool() {}
	Objective* get_next_Objective();
};

class Build_Other_Structures : public Objective
{
public:
	Build_Other_Structures()
	{ message = "Switch to Other Stuctures and build them"; }
	~Build_Other_Structures() {}
	Objective* get_next_Objective();
};

class Throw_Snowball_At_Enemy : public Objective
{
public:
	Throw_Snowball_At_Enemy()
	{ message = "Throw Snowballs with right trigger to defeat enemies!";}
	~Throw_Snowball_At_Enemy() {}
	Objective* get_next_Objective();
};

class Pack_Snowball : public Objective
{
public:
	Pack_Snowball()
	{ message = "Hold the trigger down to pack and make a larger snowball"; }
	~Pack_Snowball() {}
	Objective* get_next_Objective();
};

class Scoop_Snow : public Objective
{
public:
	Scoop_Snow()
	{ message = "Press B to scoop up snow, you must be on a soft snow tile";}
	~Scoop_Snow() {}
	Objective* get_next_Objective();
};

class Destroy_Structures : public Objective
{
public: 
	Destroy_Structures()
	{ message = "Destroy Enemy Stuctures by shooting snowballs at them";}
	Objective* get_next_Objective();
};

class Raise_Lower_Tiles : public Objective
{
public:
	Raise_Lower_Tiles()
	{ message = "Press up and down on the dpad to raise and lower tiles"; }
	Objective* get_next_Objective();
};

class Build_a_Chain_To_Tree : public Objective
{
public:
	Build_a_Chain_To_Tree()
	{ message = "Build a connected set of tiles to the tree!";}
	Objective* get_next_Objective();
};

class Destroy_Key_Enemy_Structures : public Objective
{
public:
	Destroy_Key_Enemy_Structures()
	{ message = "Destroy key enemy structures to disconnect them from the enemy base, and they will all disappear!";}
	Objective* get_next_Objective();
};

class Rescue_Your_Network : public Objective
{
public:
	Rescue_Your_Network()
	{ message = "The Enemy has disconnected your network, reconnect it with buildings before it disappears!";}
	Objective* get_next_Objective();
};

class Claim_The_Tree : public Objective
{
public:
	Claim_The_Tree()
	{ message = "Build on the Tree to claim it for your team!";}
	Objective* get_next_Objective();
};

class Defend_Your_Claim : public Objective
{
public:
	Defend_Your_Claim()
	{ message = "Defend the tree for 20 seconds by destroying enemies next to it, or reclaiming it as your own!";}
	Objective* get_next_Objective();
};

//Win??

#endif
