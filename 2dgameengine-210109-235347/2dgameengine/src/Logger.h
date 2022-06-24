#ifndef LOGGER_H
#define LOGGER_H

#include <string.h>
#include <iostream>
#include <chrono>
#include <ctime>

class Logger
{
	public:
		static void Log(const std::string& message);
		static void Err(const std::string& message);
};

#endif