
#ifndef RECEIVINGSTATION_H_
#define RECEIVINGSTATION_H_

#include "Packet.h"

#include<vector>
#include <iostream>
#include "logger.h"

class ReceivingStation
{
private:
	int StationNumber_; //number of current station
	std::vector<Packet> received; //vector of current packet that are succesfully transmited
	Logger* log_ = nullptr;

public:
	ReceivingStation(int StationNumber, Logger* logger); //constructor of object
	~ReceivingStation(); //deconstructor of object 


	void Set_ACK(); //function setting confirmation of transmission
	void AddToReceived(Packet packet); //function adding packet to vector if they are succesfully transmited
	int return_StationNumber();
};

#endif RECEIVINGSTATION_H_