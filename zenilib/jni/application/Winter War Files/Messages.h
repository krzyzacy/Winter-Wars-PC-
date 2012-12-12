
#include <zenilib.h>

#include <list>

class Message
{
public:
	Message(const Zeni::String &msg_ = "", float time_ = -10) ;

	bool is_over(Zeni::Chronometer<Zeni::Time> &timer) const;

	Zeni::String msg;

private:
	float time;
};

class Message_Queue
{
public:
	Message_Queue();

	void insert(Message &);
	void put_back(Message &);

	Message get_next();

	bool is_empty();
	
private:
	std::list<Message> Messages;
};


class All_Messages
{
public:
	All_Messages();

	void insert_priority(Message &);

	Message &get_next();

	void next_tip();

	void show_tips();
	void hide_tips();
	bool is_tip_on_screen() {return tip_on_screen;}

	bool has_message();

private:
	Zeni::Chronometer<Zeni::Time> timer;
	bool cur_is_tip;
	bool tip_on_screen;
	Message curMessage;
	Message_Queue priority;
	Message_Queue tips;
};
