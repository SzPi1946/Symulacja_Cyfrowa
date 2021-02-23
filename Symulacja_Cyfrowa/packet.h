#ifndef Packet_H_
#define Packet_H_
#include <functional>
#include <queue>
#include <vector>
#include "logger.h"
#include "process.h"

class Wirelessnetwork;

class Packet 
{
public:
	enum class State { New, Access, DrawingDIFS, SettingTransmission, SettingTransmission2, Transmission, Retransmission, Response, End }; //state for Execute
	typedef std::priority_queue<Packet*, std::vector<Packet*>, std::function<bool(Packet*, Packet*)>> Agenda; //priority queue
	Packet(int tx_id, int packet_id, Wirelessnetwork* wireless_network, Logger* logger, Agenda* agenda);		//class constructor
	~Packet();
	void Execute(); 
	void Activate(double time, bool relative = true);

	int return_tx_id();			//function to return packet_id_
	int return_w_min();			//function to return cw_min_
	int return_cw_max();		//function to return cw_max_
	int return_cw();			//function to return cw
	int return_packet_id();     //function to return packet id
	void set_cw();				//function to set cw
	void set_bt();				//function to set BT
	void set_collision(Logger* logger);
	void add_to_channel(Packet* packet);
	double get_time();
	bool return_end();
private:
	bool end_ = false;
	double time_;
	bool ack_;
	bool collision;
  double difs_;     //difs wait time counter;
	int tx_id_;		  //station id
	int packet_id_;   //generated packet id
	int cw_min_;      //beginning cw
	int cw_max_;      //end cw
	int cw_;          //size cw
	int bt_;          //rand%cw

	State state_ = State::New; //current state for Execute()
	Wirelessnetwork* wireless_network_; 
	Logger* logger_;
	Agenda* agenda_ = nullptr;
};
#endif



