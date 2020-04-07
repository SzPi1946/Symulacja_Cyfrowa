#include "Packet.h"

Packet::Packet()
{
	packet_number_ = 0; //number of current packet
	station_number_ = 0;//number of station from which packet is transmiting
	generation_time_ = 0;//the time when the packet was generated
	service_start_ = 0;//the time we stated working on the packet
	service_end_ = 0;//the time we ended working on the packet
	transmission_time_ = 0;  //full time of transmission
	ack_ = false;//confirmation that the transmission was successful or not
}

Packet::~Packet()
{
}