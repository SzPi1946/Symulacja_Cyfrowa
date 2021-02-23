#include "logger.h"

#include <iostream>

Logger::Logger()
{
	std::cout << "Logger Has Been Created." << std::endl;
	txt_file_.open("date_txt.txt", std::ios::out);
}

Logger::~Logger()
{
	std::cout << "Logger Has Been Removed." << std::endl;
}

void Logger::set_level(Level level)
{
	level_ = level;
}

void Logger::Info(std::string message)
{
	std::cout << "[Info] " << message << std::endl;
	txt_file_ << "[Info] " << message << std::endl;

}

void Logger::Debug(std::string message)
{
	std::cout << "[Debug] " << message << std::endl;
}

void Logger::Error(std::string message)
{
	std::cout << "[Error] " << message << std::endl;
}