#ifndef WIRELESSNETWORK_H_
#define WIRELESSNETWORK_H_
#include "BroadcastStation.h"
#include "ReceivingStation.h"
#include <iostream>
#include "channel.h"
#include "logger.h"
#include "Packet.h"
#include <queue>

class WirelessNetwork
{

public:
	WirelessNetwork(Logger *logger); //constructor of object
	~WirelessNetwork(); //deconstructor of object 
	bool ChannelState(); // returning channel state

	std::vector<BroadcastStation*> broadcast_station; //Broadcast Stations
	std::vector<ReceivingStation*> receiving_station; //Receiving Stations

	const int NumberOfStations_ = 8;  //number of all station after which I'm going to average out
	
	std::vector<BroadcastStation*>get_broadcast_stations();
	std::vector<ReceivingStation*>get_receiving_stations();
	Packet* get_queue(int i);
	std::vector<Packet*>get_unreceived_packets();

	void GeneratePacket(int Number); //function to generate packet

	Channel* return_channel();

private:
	Logger* log_ = nullptr;
	Channel* channel_; //new channel 
	std::vector<Packet*> queue_; //queue of packet ready to transmit 

	std::vector<Packet*> unreceived_packets; //packets with errors in transmission and couldnt be retransmited

};

#endif WIRELESSNETWORK_H_