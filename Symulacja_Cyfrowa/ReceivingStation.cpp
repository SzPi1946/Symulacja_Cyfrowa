#include "ReceivingStation.h"
#include <iostream>

ReceivingStation::ReceivingStation(int StationNumber, Logger* logger)
{
  StationNumber_ = StationNumber;
  log_ = logger;
  log_->Info("The Receiving Station " + std::to_string(StationNumber_) + " has been created.");
}

ReceivingStation::~ReceivingStation()
{
  log_->Info("The Receiving Station " + std::to_string(StationNumber_) + " has been removed.");
}

void ReceivingStation::Set_ACK()
{
}

void ReceivingStation::AddToReceived(Packet packet)
{
}

int ReceivingStation::return_StationNumber()
{
  return StationNumber_;
}