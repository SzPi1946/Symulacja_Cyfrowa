#ifndef BroadcastStation_H_
#define BroadcastStation_H_
#include <queue>
#include <iostream>
#include "Packet.h"
#include "logger.h"

class BroadcastStation
{
private:
	int StationNumber_; //number of current station
	bool block_; //variable determining if station currently transmiting or not

	Logger* log_ = nullptr;

public:
	BroadcastStation(int StationNumber, Logger* logger);
	~BroadcastStation();
	int return_StationNumber();
	const int All_Stations_ = 8; //number of all station after which I'm going to average out
	void Wait(); //function that delayed transmission 0.5s
	void WaitCGP(); //function that delayed geration of packet
	void GenerationTime(); // generate CGPk for packet
	void TransmissionTime(); // generate CTPk for packet
	void RetransmissionTime(); //generate retransmission time for packet
	//void AddToQueue(Packet* packet); //function adding new packets to queue
};

#endif BroadcastStation_H_
