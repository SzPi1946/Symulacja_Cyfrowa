#include <iostream>


#include "WirelessNetwork.h"
#include "BroadcastStation.h"
#include "ReceivingStation.h"
#include "Packet.h"
#include "channel.h"
#include "logger.h"



int main(int argc, char* argv[])
{

	Logger* logger = new Logger();
	logger->set_level(Logger::Level::Info);
	WirelessNetwork* Network = new WirelessNetwork(logger);;
	
	
	delete Network;

	delete logger;

	return 0;
}