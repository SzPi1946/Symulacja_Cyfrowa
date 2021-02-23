#include <iostream>
#include <iterator>
#include "logger.h"
#include "simulation.h"
#include "wirelessnetwork.h" 
#include "generator.h"
#include <queue>


int main()
{
	
  ////////////////////////////////////////////
	std::fstream seeds;
	seeds.open("./seeds_10.txt"); 
	std::string seedfile;
	std::queue <int> seed_;
	for (int j = 0; j < 25; j++)
	{
		std::getline(seeds, seedfile);
		seed_.push(stoi(seedfile));
	}
	///////////////////////////////////////////////
	///
	Logger* logger = new Logger();
	logger->set_level();
	double time; //Simulation time
	double lam; //Lambda Value
	double start; //Lambda Value
	std::cout << "Enter simulation time: ";
	std::cin >> time;
	std::cout << "Enter Lambda Value: ";
	std::cin >> lam;
	std::cout << "Enter Starting Phase: ";
	std::cin >> start;
	int mode = 0; //mode type on simulation 
	std::cout << "Continuous simulation -> 1  OR  Step simulation -> 2 ";
	while (mode != 1 && mode != 2) std::cin >> mode;

	Wirelessnetwork* network = new Wirelessnetwork(logger,lam,&seed_); 
	Simulation* simulation = new Simulation(network, logger);

	simulation->Run(time, mode,start); //starting simulation

	logger->Info(" ");
	simulation->DisplayData(); //Statistics
	logger->Info(" ");

	delete network;
	delete logger;
	delete simulation;
	return 0;

}
