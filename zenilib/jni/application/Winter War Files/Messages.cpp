#include "Messages.h"	

using namespace Zeni;

Message::Message(const String &msg_, float time_) :
		msg(msg_), time(time_)
{
		
}

		
bool Message::is_over(Chronometer<Time> &timer) const
{ 
	// it will always be over
	if (msg == "")
		return true;

	// it will never be over
	if (time == -10)
		return false;
	
	return  (time - timer.seconds()) < 0;
}

Message_Queue::Message_Queue() 
{
	
}

void Message_Queue::insert(Message &m)
{
	Messages.push_back(m);
}

void Message_Queue::put_back(Message &m)
{
	Messages.push_front(m);
}

Message Message_Queue::get_next()
{
	Message m = Messages.front();
	Messages.pop_front();

	return m;
}

bool Message_Queue::is_empty()
{
	return Messages.empty();
}

All_Messages::All_Messages() : cur_is_tip(false), curMessage(Message("")), tip_on_screen(true)
{
	timer.start();

	/* Put Tips in here */ 
	/* If no time is specified, it will last until tips are turned off*/
	tips.insert(Message("Build something on a tile in front you!",2));
	tips.insert(Message("Go kill a player, hold the trigger to shoot bigger Snowballs!",2));
	tips.insert(Message("Run away!  You gonna die.",2));
	tips.insert(Message("Do You really need another tip?  You dumb.",2));
}

void All_Messages::insert_priority(Message &m)
{
	priority.insert(m);
}

Message &All_Messages::get_next()
{
	if (!priority.is_empty())
	{
		cur_is_tip = false;
		tip_on_screen = false;
		curMessage = priority.get_next();
		timer.stop();
		timer.reset();
		return curMessage;
	}
	
	if (!curMessage.is_over(timer))
		return curMessage;
	
	curMessage = Message("");
	cur_is_tip = false;
/*
	if (!cur_is_tip && tip_on_screen)
	{
		// make cur the tip on top
		Message m = Message(tips.get_next());
		tips.put_back(m);
		curMessage = m;
		timer.stop();
		timer.reset();
		tip_on_screen = true;
		cur_is_tip = true;
	}
*/
	return curMessage;
}

void All_Messages::next_tip()
{
	if (tip_on_screen)
	{
		Message M = tips.get_next();
		tips.insert(M);
		priority.insert(M);
		//tips.get_next();
	}
}

bool All_Messages::has_message()
{
	return curMessage.is_over(timer);
}

void All_Messages::show_tips()
{
	tip_on_screen = true;
}

void All_Messages::hide_tips()
{
	tip_on_screen = false;
}