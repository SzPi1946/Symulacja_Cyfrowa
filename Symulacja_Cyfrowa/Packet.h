#ifndef PACKET_H_
#define PACKET_H_
#include "logger.h"
#include <iostream>
#include <queue>
#include "BroadcastStation.h"

class WirelessNetwork;


class Packet
{

	

public:
	Packet(WirelessNetwork* Network, int number, Logger* logger,int station_number); //constructor 
	~Packet(); //deconstructor
	
	int return_packet_number();  //function returning packet_number_
	int return_station_number();  //function returning station_number_
	int return_service_start(); //function returning service_start_
	int return_service_end(); //function returning service_end_
	int return_transmission_time(); //function returning transmission_time_ 
	int return_generation_time(); //function returning generation_time_ 
	int return_cw_min();
	int return_cw_max();
	int return_cw();

	int return_ack();  //function returning ack_ 

	enum class State { Access, Transmission,Response, ReTransmission, End };

	State state_ = State::Access;

	void Execute();

private: 
	int cw_min_;
	int cw_max_;
	int cw_;
	int packet_number_; //number of current packet
	int station_number_; //number of station from which packet is transmiting
	int generation_time_; //the time when the packet was generated
	int service_start_;//the time we stated working on the packet
	int service_end_; //the time we ended working on the packet
	int transmission_time_;  //full time of transmission
	bool ack_;//confirmation that the transmission was successful or not
	WirelessNetwork* network_; 
	Logger* log_ = nullptr;

}; 

#endif PACKET_H_