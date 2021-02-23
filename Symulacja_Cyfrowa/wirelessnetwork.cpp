#include "wirelessnetwork.h"

Wirelessnetwork::Wirelessnetwork(Logger* logger,double lambda, std::queue<int>* seeds)
{
	logger_ = logger;
	lambda_ = lambda;
	channel = new Channel(logger_,this); //generate channel
	ter_generator = new UniformGenerator(seeds->front());
	seeds->pop();
	for (int i = 0; i < k_; ++i)
	{
		int ctpk_seed = seeds->front();
		seeds->pop();
		int cgpk_seed = seeds->front();
		seeds->pop();
		int bt_seed = seeds->front();
		seeds->pop();
	  tx_station.push_back(new broadcaststation(i, logger, lambda_,ctpk_seed,cgpk_seed,bt_seed));
	}
	  logger_->Debug("The network has been created.");
}

Wirelessnetwork::~Wirelessnetwork()

{
	tx_station.clear();
	logger_->Debug("The network has been removed.");
	delete ter_generator;
	delete channel;
}


int Wirelessnetwork::return_number_of_stations()
{
	return k_;
}

std::vector<broadcaststation*>* Wirelessnetwork::get_tx_stations()
{
	return &tx_station;
}



Channel* Wirelessnetwork::return_channel()
{
	return channel;
}


double Wirelessnetwork::ReturnAverageTer() //œrednia wartoœæ b³êdu
{
	double value = 0.0;
	for (int i = 0; i < k_; ++i)
	{
		value += this->get_tx_stations()->at(i)->ReturnTerData();
	}
	return (value / k_);
}


double Wirelessnetwork::ReturnAverage() //œrednia wartoœæ b³êdu
{
	double value = 0.0;
	double lost = 0.0;
	for (int i=0;i<k_;++i)
	{
	value += this->get_tx_stations()->at(i)->return_counter_received();
	lost+= this->get_tx_stations()->at(i)->return_counter_lost();
	}
	return (lost / value)/k_;
}

double Wirelessnetwork::return_retransmission()
{
	double added = 0.0;
	double lost = 0.0;
	double all;
	double avarage_ret = 0.0;
	for (int i = 0; i < k_; ++i)
	{
		added += this->get_tx_stations()->at(i)->return_counter_received();
		lost += this->get_tx_stations()->at(i)->return_counter_lost();
	}
	all= added + lost;
	avarage_ret =  retransmission /all ;
	return avarage_ret;
}

void Wirelessnetwork::retransmission_add()
{
	retransmission += 1;
}

double Wirelessnetwork::SystemBitRate()
{
	double value=0.0;
	for (int i = 0; i < k_; ++i)
	{
		value += get_tx_stations()->at(0)->return_counter_received();
	}
	return value/60;
}

double Wirelessnetwork::ReturnMaxError()
{
	double max_value = this->get_tx_stations()->at(0)->ReturnTerData();
	for (int i = 1; i < k_; ++i)
	{
		if (max_value < this->get_tx_stations()->at(i)->ReturnTerData())
		{
			max_value = this->get_tx_stations()->at(i)->ReturnTerData();
		}
	}
	return max_value;
}

double Wirelessnetwork::ReturnAverageACK()
{
	double value_1 = 0.0;
	double value_2 = 0.0;
	for (int i = 0; i < k_; ++i)
	{
		value_1 += this->get_tx_stations()->at(i)->return_ctpk();
		value_2 += this->get_tx_stations()->at(i)->return_counter_received();
	}
	return (static_cast<double>(value_1) / static_cast<double>(value_2));
}

double Wirelessnetwork::ReturnAverageTime()
{
	double value = 0.0;
	for (int i = 0; i < k_; ++i)
	{
		value += get_tx_stations()->at(0)->return_counter_received();
	}

	double value_1 = 0.0;
	for (int i = 0; i < k_; ++i)
	{
		value_1 += this->get_tx_stations()->at(i)->return_cgpk();
	}

	return value_1 / value;
}

double Wirelessnetwork::ReturnTer()
{
	return ter_generator->RandZeroOne(0.8);
}
