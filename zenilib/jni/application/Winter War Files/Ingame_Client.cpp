

#include "Ingame_Client.h"


void Ingame_Client::initialize(bool isServer)
{

}

void Ingame_Client::send(WWEvent * e)
{
	Ingame_Peer::send(e);
}