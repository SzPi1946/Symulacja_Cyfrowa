#ifndef CHANNEL_H_
#define CHANNEL_H_

#include <queue>

#include "Packet.h"

class channel
{
public:
	channel(); //constructor
	~channel(); //deconstructor 

	bool free_; //variable determining if channel is busy or free
	bool collision_; //variable determining if collision happend or transsmision is free of collison

	void CheckError(); //function checking for error / collision in channel
	void CSMA_CA(); //our protocol which will be used in transmission
};

#endif CHANNEL_H_