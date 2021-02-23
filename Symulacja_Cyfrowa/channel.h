#ifndef CHANNEL_H_
#define CHANNEL_H_

#include <queue>
#include <iostream>
#include "Packet.h"
#include "logger.h"

class Channel
{
public:
	Channel(Logger* logger); //constructor
	~Channel(); //deconstructor 

	bool return_free();
	bool return_collision();

private:
	bool free_=true; //variable determining if channel is busy or free
	bool collision_; //variable determining if collision happend or transsmision is free of collison
	Logger* log_ = nullptr;
	void CheckError(); //function checking for error / collision in channel
	void Set_Status(bool status); //function setting status to channel
	void CSMA_CA(); //our protocol which will be used in transmission
	
};

#endif CHANNEL_H_