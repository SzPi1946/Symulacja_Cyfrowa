#include "simulation.h"
#include <iomanip>
#include <iostream>
#include <iterator>

#include "wirelessnetwork.h"
#include "packet.h"
#include "logger.h"


Simulation::Simulation(Wirelessnetwork* wirelessnetwork, Logger* logger)
{
	wirelessnetwork_ = wirelessnetwork;
	logger_ = logger;
}

Simulation::~Simulation()
{
}


void Simulation::Run(double time, int mode, double start_)
{
	clock_ = 0;
	auto cmp = [](Packet* left, Packet* right) {return left->get_time() > right->get_time(); };
	Packet::Agenda agenda_(cmp);
	for (int i = 0; i < wirelessnetwork_->return_number_of_stations(); ++i)
	{
		wirelessnetwork_->get_tx_stations()->at(i)->create_packet(wirelessnetwork_, &agenda_); //
		wirelessnetwork_->get_tx_stations()->at(i)->return_txbuffor()->front()->Activate(0);
	}


	std::cout.precision(2);
	std::cout.setf(std::ios::fixed, std::ios::floatfield);
	std::cout << "[TIME]" << std::setw(7) << clock_ << std::endl;
	//////////////////////////MAIN LOOP//////////////////////////////
	while (clock_ < time && !agenda_.empty())
	{
		if(clock_==start_)
		{
			for (int i = 0; i < wirelessnetwork_->return_number_of_stations(); ++i)
			{
				wirelessnetwork_->get_tx_stations()->at(i)->reset_counters();
			}
		}
		Packet* help = agenda_.top(); 
		clock_ = help->get_time();
		agenda_.pop();
		if (clock_2 != clock_)
		{
			clock_2 = clock_;
			std::cout << "[TIME] " << std::setw(7) << clock_ << std::endl;
			wirelessnetwork_->return_channel()->set_status2(wirelessnetwork_->return_channel()->return_status());
			if (mode == 2) system("pause");
		}
		help->Execute();
		if (help->return_end() == true)
		{
			//logger_->Error(std::to_string(clock_) /*+ "   " + std::to_string(wirelessnetwork_->ReturnAverage())*/);
			//logger_->Error(std::to_string(wirelessnetwork_->return_retransmission())); // std::to_string(clock_)  // wirelessnetwork_->return_retransmission()
		  delete help;
		}
	}
	
}

void Simulation::DisplayData()
{
	logger_->Info("Simulation Time " + std::to_string(this->clock_));
	for (int i = 0; i < wirelessnetwork_->return_number_of_stations(); ++i)
	{
		logger_->Info("Packets in the station ID " + std::to_string(i + 1) + " buffer: " + std::to_string(wirelessnetwork_->get_tx_stations()->at(i)->return_txbuffor()->size()));
	}
	for (int i = 0; i < wirelessnetwork_->return_number_of_stations(); ++i)
	{
		logger_->Info("Station ID " + std::to_string(i + 1) + ": " + std::to_string(wirelessnetwork_->get_tx_stations()->at(i)->return_counter_received()) + " received  | "
			+ std::to_string(wirelessnetwork_->get_tx_stations()->at(i)->return_counter_lost()) + " lost");
	}
	for (int i = 0; i < wirelessnetwork_->return_number_of_stations(); ++i)
	{
		logger_->Info("Station ID " + std::to_string(i + 1) + " error rate: " + std::to_string(wirelessnetwork_->get_tx_stations()->at(i)->ReturnTerData()));
	}

	logger_->Info("Average error rate: " + std::to_string(wirelessnetwork_->ReturnAverageTer()));
	logger_->Info("Max error rate: " + std::to_string(wirelessnetwork_->ReturnMaxError()));
	logger_->Info("Retransmision rate: " + std::to_string(wirelessnetwork_->return_retransmission()));
	logger_->Info("Average packet time delay: " + std::to_string(wirelessnetwork_->ReturnAverageTime() ) + " s");
	logger_->Info("Average packet with ACK delay: " + std::to_string(wirelessnetwork_->ReturnAverageACK() ) + " s");
	logger_->Info("System bit rate: " + std::to_string(wirelessnetwork_->SystemBitRate()) + " packet/s");
	////////////////////////
	/*logger_->Error("Simulation Time " + std::to_string(this->clock_));
	for (int i = 0; i < wirelessnetwork_->return_number_of_stations(); ++i)
	{
		logger_->Error("Packets in the station ID " + std::to_string(i + 1) + " buffer: " + std::to_string(wirelessnetwork_->get_tx_stations()->at(i)->return_txbuffor()->size()));
	}
	for (int i = 0; i < wirelessnetwork_->return_number_of_stations(); ++i)
	{
		logger_->Error("Station ID " + std::to_string(i + 1) + ": " + std::to_string(wirelessnetwork_->get_tx_stations()->at(i)->return_counter_received()) + " received  | "
			+ std::to_string(wirelessnetwork_->get_tx_stations()->at(i)->return_counter_lost()) + " lost");
	}
	for (int i = 0; i < wirelessnetwork_->return_number_of_stations(); ++i)
	{
		logger_->Error("Station ID " + std::to_string(i + 1) + " error rate: " + std::to_string(wirelessnetwork_->get_tx_stations()->at(i)->ReturnTerData()));
	}

	logger_->Error("Average error rate: " + std::to_string(wirelessnetwork_->ReturnAverageTer()));
	logger_->Error("Max error rate: " + std::to_string(wirelessnetwork_->ReturnMaxError()));
	logger_->Error("Retransmision rate: " + std::to_string(wirelessnetwork_->return_retransmission()));
	logger_->Error("Average packet time delay: " + std::to_string(wirelessnetwork_->ReturnAverageTime()) + " s");
	logger_->Error("Average packet with ACK delay: " + std::to_string(wirelessnetwork_->ReturnAverageACK()) + " s");
	logger_->Error("System bit rate: " + std::to_string(wirelessnetwork_->SystemBitRate()) + " packet/s");*/
}