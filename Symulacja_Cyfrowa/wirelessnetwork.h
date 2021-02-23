#ifndef WIRELESSNETWORK_H_
#define WIRELESSNETWORK_H_
#include <vector>
#include "broadcaststation.h"
#include "channel.h"
#include "logger.h"
#include "generator.h"

class UniformGenerator;
class Channel;
class broadcaststation;
class Wirelessnetwork
{
public:

	Wirelessnetwork(Logger* logger, double lambda, std::queue<int> * numbers);					//class constructor
	~Wirelessnetwork();									//class deconstructor
	std::vector<broadcaststation*>* get_tx_stations();
	Channel* return_channel();
	int return_number_of_stations();
	double ReturnAverageTer();
	double ReturnMaxError();
	double SystemBitRate();
	double ReturnAverageACK();
	double ReturnAverageTime();
	double ReturnTer();
	double ReturnAverage();
	double return_retransmission();
	void retransmission_add();
private:
	double lambda_;
	int retransmission;
	const int k_ = 8;									//number of station
	std::vector<broadcaststation*> tx_station;				// broadcasting station vector
	Channel* channel = nullptr;									//create channel
	Logger* logger_ = nullptr;
	UniformGenerator* ter_generator = nullptr; 

};

#endif
