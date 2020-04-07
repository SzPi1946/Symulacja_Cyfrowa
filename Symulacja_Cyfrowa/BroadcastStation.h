#ifndef BroadcastStation_H_
#define BroadcastStation_H_
#include <queue>

#include "Packet.h"

class BroadcastStation
{
public:
	BroadcastStation();
	~BroadcastStation();

	int StationNumber_; //number of current station
	const int All_Stations_ = 8; //number of all station after which I'm going to average out
	bool block; //variable determining if station currently transmiting or not

	std::queue<Packet> queue; //queue of packet ready to transmit 

	void Wait(); //function that delayed transmission 0.5s
	void WaitCGP(); //function that delayed geration of packet
	void GenerationTime(); // generate CGPk for packet
	void TransmissionTime(); // generate CTPk for packet
	void RetransmissionTime(); //generate retransmission time for packet
	Packet GeneratePacket(); //function to generate packet
	void AddToQueue(Packet packet); //function adding new packets to queue
};

#endif BroadcastStation_H_
