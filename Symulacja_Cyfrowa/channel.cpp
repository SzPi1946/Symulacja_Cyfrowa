#include "channel.h"
#include <iostream>
#include "logger.h"

Channel::Channel(Logger* logger, Wirelessnetwork* network)
{
	network_ = network;
	status2 = true;
	status = true;
	logger_ = logger;
	logger_->Debug("The channel has been created.");
}
Channel::~Channel()
{
	logger_->Debug("The channel has been removed.");
}

bool Channel::return_status()
{
	return status;
}

void Channel::set_free(Logger* logger)
{
	logger->Debug("Channel status setting free.");
	status = true;
}

double Channel::return_ack()
{
	return ctiz_;
}

int Channel::return_ter()
{
 return network_->ReturnTer();
}

void Channel::add_packet(Packet* packet)
{
	packets_.push_back(packet);

	if (packets_.size() >= 2)
	{
		for (int i = 0; i < packets_.size(); i++)
		{
			packets_.at(i)->set_collision(logger_);
		}
	}

}

void Channel::delete_packet(int packet_id, int station_id)
{
	for (int i = 0; i < packets_.size(); i++)
		if (packets_[i]->return_packet_id() == packet_id && packets_[i]->return_tx_id() == station_id)
			packets_.erase(packets_.begin() + i);
}

std::vector<Packet*>* Channel::return_packets()
{
	return &packets_;
}


void Channel::set_status2(bool status)
{
	status2 = status;
}

bool Channel::return_status2()
{
	return status2;
}


void Channel::set_busy(Logger* logger)
{
	logger->Debug("Channel status setting busy.");
	status = false;
}




