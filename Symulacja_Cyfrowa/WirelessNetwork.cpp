#include "WirelessNetwork.h"
#include <iostream>

#include "BroadcastStation.h"
#include "ReceivingStation.h"
#include "channel.h"
#include "Packet.h"
#include <queue>

WirelessNetwork::WirelessNetwork(Logger* logger)
{
	log_ = logger;
	channel_ = new Channel(logger); //generate channel
	log_->Info("The network has been created.");
	for (int i = 1; i < NumberOfStations_+1; ++i)
	{
		broadcast_station.push_back(new BroadcastStation(i, logger));
		receiving_station.push_back(new ReceivingStation(i, logger));
	//for
	//id = Network->broadcast_station[i]->return_StationNumber();
	//id - 0
	}
	this->GeneratePacket(1); //Generate Packet will be in this for function, and the time wil be added to it constructor
	this->get_queue(1)->Packet::Execute();
}

WirelessNetwork::~WirelessNetwork()
{
	for (int i = 1; i < NumberOfStations_ +1; ++i)
	{
		delete broadcast_station[i];
		delete receiving_station[i];
	}

	broadcast_station.clear();

	receiving_station.clear();

	delete channel_;

	log_->Info("The network has been removed.");
}

std::vector<BroadcastStation*> WirelessNetwork::get_broadcast_stations()
{
	return broadcast_station;
}

std::vector<ReceivingStation*> WirelessNetwork::get_receiving_stations()
{
	return receiving_station;
}



Channel* WirelessNetwork::return_channel()
{
	return channel_;
}

void WirelessNetwork::GeneratePacket(int Number)
{

	Logger* log_ = nullptr;
	int id = this->broadcast_station[1]->return_StationNumber();
	for (int i = 0; i < 5; ++i)
	{
		queue_.push_back(new Packet(this, Number, log_, id));
	}

}


Packet* WirelessNetwork::get_queue(int i)
{
	return queue_[i];
}

std::vector<Packet*> WirelessNetwork::get_unreceived_packets()
{
	return unreceived_packets;
}

bool WirelessNetwork::ChannelState()
{
	return channel_->return_free();
}