#ifndef WIRELESSNETWORK_H_
#define WIRELESSNETWORK_H_
#include "BroadcastStation.h"
#include "ReceivingStation.h"

class WirelessNetwork
{
public:
	WirelessNetwork(); //constructor of object
	~WirelessNetwork(); //deconstructor of object 

	const int NumberOfStations = 8;  //number of all station after which I'm going to average out
	std::vector<BS*> broadcast_stations; //Broadcast Stations
	std::vector<RS*> receiving_stations; //Receiving Stations
	std::vector<Packet> unreceived_packets; //packets with errors in transmission and couldnt be retransmited

};

#endif WIRELESSNETWORK_H_