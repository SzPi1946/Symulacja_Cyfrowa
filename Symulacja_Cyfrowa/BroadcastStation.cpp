#include "BroadcastStation.h"
#include "WirelessNetwork.h"
#include <iostream>
#include "logger.h"
#include <queue>
#include "Packet.h"

BroadcastStation::BroadcastStation(int StationNumber, Logger* logger)
{
	log_ = logger;
	StationNumber_ = StationNumber;
	log_->Info("The Broadcast Station " + std::to_string(StationNumber_) + " has been created.");
}

BroadcastStation::~BroadcastStation()
{
	log_->Info("The Broadcast Station " + std::to_string(StationNumber_) + " has been removed.");
}



void BroadcastStation::RetransmissionTime()
{
	
}

void BroadcastStation::GenerationTime()
{
	
}

void BroadcastStation::TransmissionTime()
{
	
}

//void BroadcastStation::AddToQueue(Packet* packet)
//{
	
//}

void BroadcastStation::Wait()
{

}

void BroadcastStation::WaitCGP()
{

}

int BroadcastStation::return_StationNumber()
{
	return StationNumber_;
}