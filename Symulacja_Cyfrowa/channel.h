#ifndef CHANNEL_H_
#define CHANNEL_H_
#include <vector>
#include "logger.h"
#include "packet.h"
#include "wirelessnetwork.h"

class Channel
{
public:
	Channel(Logger* logger,Wirelessnetwork* network);						//class constructor
	~Channel();						//class deconstructor
	bool return_status();			//function return channel status
	void set_free(Logger* logger);	 //function to set channel status
	void set_busy(Logger* logger); //function to set channel status
	double return_ack(); //returning ctiz time
	int return_ter(); //returning value of TER
	void add_packet(Packet* packet); //adding packet to vector 
	void delete_packet(int packet_id, int station_id); //deleting packet from channel
	std::vector<Packet*>* return_packets(); //returning packet from vector 
	void set_status2(bool status); //setting status2 
	bool return_status2(); //returning status2
private:
	std::vector<Packet*> packets_; //vector of packets
	Wirelessnetwork* network_=nullptr; 
  double ctiz_ = 1.0;       //ack time
	bool status;			//channel status
	bool status2;			//channel status
	Logger* logger_ = nullptr;
};
#endif



