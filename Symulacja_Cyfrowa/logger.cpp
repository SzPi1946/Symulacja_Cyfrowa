#include "logger.h"
#include <iostream>

Logger::Logger()
{
	txt_file_.open("date_txt.txt", std::ios::out);
}

Logger::~Logger()
{
}

void Logger::set_level()
{
	int a;
	std::cout << "Info->1  Debug->2  Error->3 ";
	while (true)
	{
		std::cin >> a;
		if ((a >= 1) || (a <= 3)) break;
	}
	if (a == 1) level_ = Level::Info;
	if (a == 2) level_ = Level::Debug;
	if (a == 3) level_ = Level::Error;
}

void Logger::Info(std::string message)
{
	if (level_ != Level::Error)
	{
		std::cout << "[Info] " << message << std::endl;
	  txt_file_ << "[Info] " << message << std::endl;
	}

}

void Logger::Debug(std::string message)
{
	if (level_ == Level::Debug)
	{
		std::cout << "[Debug] " << message << std::endl;
	  txt_file_ << "[Debug] " << message << std::endl;
	}

}

void Logger::Error(std::string message)
{

	//std::cout << "[Error] " << message << std::endl;
  txt_file_ <<  message << std::endl; // "[Error]" <<


}
