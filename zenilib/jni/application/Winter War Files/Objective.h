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

class Use_Tips : public Objective
{
public:
	Use_Tips();
	~Use_Tips() {}
	Objective* get_next_Objective();
	bool has_been_completed();

};

class Build_Structure : public Objective
{
public:
	Build_Structure(int type_);
	~Build_Structure() {}
	Objective* get_next_Objective();
	bool has_been_completed();

private:
	int type;
};

class Build_Other_Structures : public Objective
{
public:
	Build_Other_Structures();
	~Build_Other_Structures() {}
	Objective* get_next_Objective();
	bool has_been_completed();
};

class Throw_Snowball_At_Enemy : public Objective
{
public:
	Throw_Snowball_At_Enemy();
	~Throw_Snowball_At_Enemy() {}
	Objective* get_next_Objective();
	bool has_been_completed();
};

class Pack_Snowball : public Objective
{
public:
	Pack_Snowball();
	~Pack_Snowball() {}
	Objective* get_next_Objective();
	bool has_been_completed();
};

class Scoop_Snow : public Objective
{
public:
	Scoop_Snow();
	~Scoop_Snow() {}
	Objective* get_next_Objective();
	bool has_been_completed();

private:
	float start_scooped;
};

class Destroy_Structures : public Objective
{
public: 
	Destroy_Structures();
	~Destroy_Structures() {}
	Objective* get_next_Objective();
	bool has_been_completed();
};

class Raise_Lower_Tiles : public Objective
{
public:
	Raise_Lower_Tiles();
	Objective* get_next_Objective();
	bool has_been_completed();
};

class Build_a_Chain_To_Tree : public Objective
{
public:
	Build_a_Chain_To_Tree();
	Objective* get_next_Objective();
	bool has_been_completed();
};

class Destroy_Key_Enemy_Structures : public Objective
{
public:
	Destroy_Key_Enemy_Structures();
	Objective* get_next_Objective();
	bool has_been_completed();
};

class Rescue_Your_Network : public Objective
{
public:
	Rescue_Your_Network();
	Objective* get_next_Objective();
	bool has_been_completed();
private:
	bool snowballs_caused_disconnect;
};

class Claim_The_Tree : public Objective
{
public:
	Claim_The_Tree();
	Objective* get_next_Objective();
	bool has_been_completed();
};

class Defend_Your_Claim : public Objective
{
public:
	Defend_Your_Claim();
	Objective* get_next_Objective();
	bool has_been_completed();
private:
	Zeni::Chronometer<Zeni::Time> wait_to_claim_tree;
	int claim_count;
};

//Win??

#endif
