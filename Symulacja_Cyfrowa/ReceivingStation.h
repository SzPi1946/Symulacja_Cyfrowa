
#ifndef RECEIVINGSTATION_H_
#define RECEIVINGSTATION_H_

#include "Packet.h"

#include<vector>

class ReceivingStation
{
public:
	ReceivingStation(); //constructor of object
	~ReceivingStation(); //deconstructor of object 

	int StationNumber_; //number of current station

	std::vector<Packet> received; //vector of current packet that are succesfully transmited

	void Set_ACK(); //function setting confirmation of transmission
	void AddToReceived(Packet packet); //function adding packet to vector if they are succesfully transmited
};

#endif RECEIVINGSTATION_H_