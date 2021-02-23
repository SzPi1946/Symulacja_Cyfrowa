#include "packet.h"
#include "wirelessnetwork.h"
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <cstdlib>

Packet::Packet(int tx_id, int packet_id, Wirelessnetwork* wireless_network, Logger* logger, Agenda* agenda) : wireless_network_(wireless_network), logger_(logger)
{
	wireless_network_ = wireless_network;
  agenda_ = agenda;
	tx_id_ = tx_id;
	packet_id_ = packet_id;
}

Packet::~Packet()
{
	logger_->Debug("Station: " + std::to_string(tx_id_) + " id: " + std::to_string(packet_id_) + " deleted.");
}

void Packet::Execute()
{

	bool active = true;

	while (active)
	{
		switch (state_)
		{
		case State::New:
		{
			logger_->Info(" Station: " + std::to_string(tx_id_) + " has created new packet id: " + std::to_string(packet_id_));
		  Packet* help = new Packet(tx_id_, packet_id_ + 1, wireless_network_, logger_, agenda_);
			help->time_ = time_;
			help->Activate(wireless_network_->get_tx_stations()->at(tx_id_)->return_cgpk());
			wireless_network_->get_tx_stations()->at(tx_id_)->return_txbuffor()->push(help);
			wireless_network_->get_tx_stations()->at(tx_id_)->packet_counter(); //adding packet to counter to statistics
			//Starting Parameters for actual packet
			collision = false;
			ack_ = false;
			cw_min_ = 15;
			cw_max_ = 255;
			cw_ = 15;
			difs_ = 0;

			state_ = State::Access;
			break;
		}
		case State::Access:
		{
			if (wireless_network_->get_tx_stations()->at(tx_id_)->return_txbuffor()->front()->return_packet_id() != packet_id_)
			{
				active = false;
			}
			else
			{
				if (difs_ == 1.0) //checking difs time
				{
					bt_=wireless_network_->get_tx_stations()->at(tx_id_)->return_bt(0,cw_);
					logger_->Info(" Station: " + std::to_string(tx_id_) + " packet id: " + std::to_string(packet_id_) + " bt_: " + std::to_string(bt_));
					state_ = State::SettingTransmission;
				}
				else
				{
				  Activate(0.5);
					state_ = State::DrawingDIFS; 
					active = false;
				}

			}
			break;
		}
		case State::DrawingDIFS: 
		{
			if (wireless_network_->return_channel()->return_status2())
			{
				
				difs_ += 0.5; //changing difs time as the channel is free
			}
			else
			{
				difs_ = 0;
			}
			state_ = State::Access;
			logger_->Debug(" Station: " + std::to_string(tx_id_) + " packet id: " + std::to_string(packet_id_) + " difs_: " + std::to_string(difs_));

		 break;
		}
		case State::SettingTransmission:
		{
			if (bt_ == 0)
			{
				state_ = State::Transmission;
			}
			else
			{
				Activate(0.5);
				state_ = State::SettingTransmission2;
				active = false;
			}

			break;
		}
		case State::SettingTransmission2:
		{
			if (wireless_network_->return_channel()->return_status2())
			{
				bt_ -= 1;
			}
			logger_->Debug(" Station: " + std::to_string(tx_id_) + " packet id: " + std::to_string(packet_id_) + " bt_: " + std::to_string(bt_));
			state_ = State::SettingTransmission;
			break;
		}
		case State::Transmission:
		{
		  
			logger_->Info(" Station: " + std::to_string(tx_id_) + " id: " + std::to_string(packet_id_) + " transmission");
			wireless_network_->return_channel()->set_busy(logger_); //Setting channel = busy 
			add_to_channel(this);
			Activate(wireless_network_->get_tx_stations()->at(tx_id_)->return_ctpk());
			//logger_->Info(" TRANS TIME / / / / / / / / / / / / /  " + std::to_string(trans_time) + "    " + std::to_string(tx_id_));
			state_ = State::Response;
			active = false;
			break;
		}
		case State::Retransmission:
		{
			logger_->Debug("Starting Retransmission. For Tx: " + std::to_string(tx_id_) + " for " + std::to_string(packet_id_));
			wireless_network_->retransmission_add();
			wireless_network_->return_channel()->delete_packet(packet_id_, tx_id_);
		  if (wireless_network_->return_channel()->return_packets()->empty())
		  {
			wireless_network_->return_channel()->set_free(logger_);
			}

			if (cw_ == cw_max_)
			{
				state_ = State::End; //checking if we can still retransmit the packet
			}
			else
			{
				collision = false;
				difs_ = 0;
				set_cw();
				state_ = State::Access;
			}
			break;
		}
		case State::Response:
		{
			logger_->Debug(" Station " + std::to_string(tx_id_) + " packet id: " + std::to_string(packet_id_) + " waiting for response.");
			Activate(wireless_network_->return_channel()->return_ack());
			logger_->Debug("Checking TER for " + std::to_string(tx_id_) + " for packet: " + std::to_string(packet_id_) +"." );
			if (collision == true || wireless_network_->return_channel()->return_ter() ==0) //checking for collision and TER error, 
			{
				state_ = State::Retransmission;
			}
			else
			{
				ack_ = true; //ACK = TRUE 
				state_ = State::End;
			}
			active = false;
			break;
		}
		case State::End:
		{
		  wireless_network_->return_channel()->delete_packet(packet_id_, tx_id_);
			if (wireless_network_->return_channel()->return_packets()->empty())
		  {
			  wireless_network_->return_channel()->set_free(logger_);
			}
			
			if (ack_ == true)
			{
				wireless_network_->get_tx_stations()->at(tx_id_)->counter_received_plus(); //adding to received 
				logger_->Info(" Station " + std::to_string(tx_id_) + " id: " + std::to_string(packet_id_) + " received correctly.");
				end_ = true;
				wireless_network_->get_tx_stations()->at(tx_id_)->return_txbuffor()->pop();
			}
			else
			{
				wireless_network_->get_tx_stations()->at(tx_id_)->counter_lost_plus(); //adding to lost
				//logger_->Error(" Station " + std::to_string(tx_id_) + " id: " + std::to_string(packet_id_) + " received incorrectly.");
				end_ = true;
				wireless_network_->get_tx_stations()->at(tx_id_)->return_txbuffor()->pop();//deleting actual packet 
			}
		  
			if (!wireless_network_->get_tx_stations()->at(tx_id_)->return_txbuffor()->empty())
			{
				if (wireless_network_->get_tx_stations()->at(tx_id_)->return_txbuffor()->front()->get_time() < time_) wireless_network_->get_tx_stations()->at(tx_id_)->return_txbuffor()->front()->Activate(time_, false);
			}
			active = false;
			
			break;
		}
    default:
	    {
	   break;
		  }
		}
	}
}


void Packet::Activate(double time, bool relative)
{
	if (relative)
	{
		time_ += time;
	}
	else
	{
		time_ = time;
	}

	agenda_->push(this);
}

int Packet::return_tx_id()
{
	return tx_id_;
}
int Packet::return_w_min()
{
	return  cw_min_;
}
int Packet::return_cw_max()
{
	return  cw_max_;
}
int Packet::return_cw()
{
	return cw_;
}
int Packet::return_packet_id()
{
	return packet_id_;
}
void Packet::set_cw()
{
	int first = (2 * (cw_ + 1)) - 1;
	int second = cw_max_;
	if (first >= second)
	{
		cw_ =  second;
	}
	else
	{
		cw_ = first;
	}
}
void Packet::set_bt()
{
//	bt_ = wireless_network_->get_tx_stations()->at(tx_id_)->return_bt()->Rand(0, cw_); //rand new value for bt_
}

void Packet::set_collision(Logger* logger)
{
	collision = true;
}

void Packet::add_to_channel(Packet* packet)
{
	wireless_network_->return_channel()->add_packet(packet);
}

double Packet::get_time()
{
	return time_;
}

bool Packet::return_end()
{
	return end_;
}
