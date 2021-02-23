#ifndef BROADCASTSTATION_H_
#define BROADCASTSTATION_H_
#include <queue>
#include "generator.h"
#include "wirelessnetwork.h"
#include "packet.h"
#include "channel.h"
#include "logger.h"
#include <functional>
#include <vector>

class Wirelessnetwork;
class UniformGenerator;
class broadcaststation
{
public:
	typedef std::priority_queue<Packet*, std::vector<Packet*>, std::function<bool(Packet*, Packet*)>> Agenda; //priority queue 
	broadcaststation(int id, Logger* logger, double lambda_wir, int s_ctpk, int s_cgpk, int s_bt);				//class constructor
	~broadcaststation();									//class deconstructor
	std::queue<Packet*>* return_txbuffor(); //returning the current last packet in buffor
	void create_packet(Wirelessnetwork* network, Agenda* agenda_); //function for packet generation 
	int return_ctpk(); //return of ctpk delay 
	int return_cgpk(); //return delay of cgpk
	int return_tx_id(); //return tx_ic_
	void packet_counter(); //updating the value of counter_
	void counter_received_plus(); //updating the value of counter_received
	void counter_lost_plus(); //updating the value of counter_lost
	int return_counter_received(); //return value of counter_received 
	int return_counter_lost(); //return value of counter_lost
	int return_counter();  //return value of counter_
  void reset_counters();  // reset statistics after starting phase 
	double ReturnTerData(); //to statistics 
	double ReturnAverage(); //to statistics 
	int return_bt(int min, int max); //returning the BT value for packet

private:
	double lambda_tx;
	int packet_id_ = 0;				//number of packet
	int counter_;
	int tx_id_;						//number of station
	int counter_received;
	int counter_lost;

	UniformGenerator* cgp_generator = nullptr; 
	UniformGenerator* ctp_generator = nullptr;
	UniformGenerator* bt_generator = nullptr;
	std::queue<Packet*> tx_buffor_; //packets to send
	Logger* logger_ = nullptr;

};

#endif




