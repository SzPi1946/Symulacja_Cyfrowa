#pragma once
class Wirelessnetwork;
class Logger;

class Simulation
{
public:
	Simulation(Wirelessnetwork* wirelessnetwork, Logger* logger);
	~Simulation();
	void Run(double time, int mode, double start);
	void DisplayData();

private:
	Wirelessnetwork* wirelessnetwork_ = nullptr;
	Logger* logger_ = nullptr;
	double clock_;
	double clock_2;
};

