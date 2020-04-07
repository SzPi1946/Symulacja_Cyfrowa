#ifndef PACKET_H_
#define PACKET_H_



class Packet
{
public:
	Packet(); //constructor 
	~Packet(); //deconstructor
	int packet_number_; //number of current packet
	int station_number_; //number of station from which packet is transmiting
	int generation_time_; //the time when the packet was generated
	int service_start_;//the time we stated working on the packet
	int service_end_; //the time we ended working on the packet
	int transmission_time_;  //full time of transmission
	bool ack_;//confirmation that the transmission was successful or not
}; 

#endif PACKET_H_