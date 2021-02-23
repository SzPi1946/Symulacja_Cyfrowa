#include "Packet.h"
#include "WirelessNetwork.h"
#include "logger.h"
#include "BroadcastStation.h"
#include "ReceivingStation.h"
#include <iostream>
#include <queue>

Packet::Packet(WirelessNetwork* Network, int number, Logger* logger,int station_number)
{

	network_ = Network;
	packet_number_ = number; //number of current packet
	station_number_=station_number;//number of station from which packet is transmiting
	generation_time_ = 0;//the time when the packet was generated
	service_start_ = 0;//the time we stated working on the packet
	service_end_ = 0;//the time we ended working on the packet
	transmission_time_ = 0;  //full time of transmission
	ack_ = false;//confirmation that the transmission was successful or not
	cw_min_ = 15; //start of the window
	cw_max_ = 255; //end of the window
	cw_ = 15; // first value
	log_ = logger;
	log_->Info("The Packet in Station " + std::to_string(station_number_) + " has been created.");
}

Packet::~Packet()
{
}

void Packet::Execute()
{
	Logger* log_ = nullptr;
	log_->set_level(Logger::Level::Debug);
	switch (state_)
	{
		case State::Access:
		{
		
			//Check DIFS
				log_->Debug("Accessing The Channel . . . . . . .");
				if (network_->ChannelState() == true)
				{
					log_->Debug(" Acces to the channel granted.");
					//Wait Difs
					bool DIFS = true;
					if (DIFS)
					{
						log_->Debug("Time DIFS Correct. ");
						State state_ = State::Transmission;
						this->Execute();
					}
					else
					{
						State state_ = State::Access;
						log_->Debug("Time DIFS Inncorect!");
						this->Execute();
					}
				}
				else
				{
					
					log_->Debug("The Channel is Busy.");
					State state_ = State::Access;
					this->Execute();
				}
			break;
		}
		case State::Transmission:
		{
		
			log_->Debug("Starting Transmission.");
			//SET BT
			//Check T=CTP+CTIZ
			//WirelessNetwork::
			log_->Debug("The Packet has been send.");

			
			State state_ = State::Response;
			this->Execute();
			break;
		}

		case State::Response:
		{

			log_->Debug("Waiting for response.");

			log_->Debug("Response delivered. Correct Transmission. ");
			State state_ = State::End;
			break;
		}

		case State::ReTransmission:
		{
			log_->Debug("Starting Retransmission.");

			log_->Debug("Waiting For Response.");
			break;
		}

		case State::End:
		{
			log_->Debug("Shuting Down The Network. Transmission Complete.");
			break;
		}
		default:
		{
			break;
		}
	}
	
}


int Packet::return_packet_number()
{
	return packet_number_;
}

int Packet::return_station_number()
{
	return station_number_;
}

int Packet::return_service_start()
{
	return service_start_;
}

int Packet::return_service_end()
{
	return service_end_;
}

int Packet::return_generation_time()
{
	return generation_time_;
}

int Packet::return_transmission_time()
{
	return transmission_time_;
}

int Packet::return_ack()
{
	return ack_;
}


int Packet::return_cw_min()
{
	return  cw_min_;
}

int Packet::return_cw()
{
	return  cw_;
}

int  Packet::return_cw_max()
{
	return  cw_max_;
}