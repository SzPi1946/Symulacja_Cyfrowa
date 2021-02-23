#include "broadcaststation.h"
#include "packet.h"
#include "wirelessnetwork.h"
#include "generator.h"
#include <iostream>

broadcaststation::broadcaststation(int id, Logger* logger, double lambda_wir, int ctpk_seed, int cgpk_seed, int bt_seed)
{
	logger_ = logger;
	tx_id_ = id;

	lambda_tx = lambda_wir;
	cgp_generator = new UniformGenerator(cgpk_seed); 
	ctp_generator = new UniformGenerator(ctpk_seed); 
	bt_generator = new UniformGenerator(bt_seed);

	counter_received = 0;
	counter_lost = 0;
}

broadcaststation::~broadcaststation()
{
	delete cgp_generator;
	delete ctp_generator;
	delete bt_generator;
	logger_->Debug("The Broadcast Station " + std::to_string(tx_id_) + " has been removed");
}

std::queue<Packet*>* broadcaststation::return_txbuffor()
{
	return &tx_buffor_;
}


void broadcaststation::create_packet(Wirelessnetwork* network, Agenda* agenda_)
{
	tx_buffor_.push(new Packet(tx_id_, packet_id_, network, logger_, agenda_));
	packet_id_++;
  
}

double broadcaststation::ReturnTerData()
{
	return (counter_lost /   static_cast<double>( counter_received ) );
}


int broadcaststation::return_ctpk()
{
	return  ctp_generator->Rand(1,10 );
}
int broadcaststation::return_cgpk()
{
	int value = ctp_generator->RandEXP(lambda_tx);
	return value;
}

int broadcaststation::return_bt(int min, int max)
{
	int value = bt_generator->Rand(min, max);
	return value;
}

int broadcaststation::return_tx_id()
{
	return tx_id_;
}

void broadcaststation::reset_counters()
{
	counter_ = 0;
	counter_received = 0;
	counter_lost = 0;
}

int broadcaststation::return_counter()
{
	return counter_;
}
void broadcaststation::counter_received_plus()
{
	counter_received += 1;
}

void broadcaststation::packet_counter()
{
	counter_ += 1;
}

void broadcaststation::counter_lost_plus()
{
	counter_lost += 1;
}

int broadcaststation::return_counter_received()
{
	return counter_received;
}

int broadcaststation::return_counter_lost()
{
	return counter_lost;
}



