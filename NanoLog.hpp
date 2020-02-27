//
//  TinyLog
//  A single-header only C++ library for easy basic logging.
//  It supports several log levels and can produce log file.
//
//  Copyright (c) 2013 SHANG Lei <shang.france@gmail.com>
//
//  This library is released under the WTFPL Licence.
//  http://www.wtfpl.net/
//
#pragma once
#ifndef TINYLOG_H
#define TINYLOG_H

#include <ostream>
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

namespace tl
{
	using namespace std;
	class TinyLog
	{

	public:
		enum LogLevel { TRACE = 1, DEBUG = 2, INFO = 3, WARNING = 4};

		///@brief Constructor.
		///@param ll Log level of the object
		///@param The output stream to use. By default we use stdout.
		TinyLog(LogLevel ll, ostream * const os = NULL)
		{
			_iLogLevel = ll;
			if (os == NULL)
				out = &cout;
			else
				out = os;
		}

		//Print log
		template<typename T>
		ostream& operator <<(const T& content)
		{
			std::time_t rawTime;
			std::time(&rawTime);
			std::tm * time = std::localtime(&rawTime);
			
			if (_iLogLevel >= TinyLog::GlobalLogLevel())
			{
				(*(out)) << "[";
				(*(out)) << time->tm_year + 1900 << '-';
				(*(out)) << std::setw(2) << std::setfill('0') << time->tm_mon + 1 << '-';
				(*(out)) << std::setw(2) << std::setfill('0') << time->tm_mday << ' ';
				(*(out)) << std::setw(2) << std::setfill('0') << time->tm_hour << ':';
				(*(out)) << std::setw(2) << std::setfill('0') << time->tm_min << ':';
				(*(out)) << std::setw(2) << std::setfill('0') << time->tm_sec << '.';
				(*(out)) << "] ";
				(*(out)) << content;
			}
			return *out;
		}

		//The global level which can be used to enable/disable log levels.
		//I use this way to avoid creating a cpp file.
		static LogLevel GlobalLogLevel(LogLevel ll = LogLevel(0))
		{
			static LogLevel GlobalLevel = DEBUG;
			if (ll != LogLevel(0)) //set level
			{
				LogLevel ret = GlobalLevel;
				GlobalLevel = ll;
				return ret;
			}
			return GlobalLevel; //For get
		}

	private:
		LogLevel _iLogLevel;	//The log level of the current TinyLog object
		ostream* out;
	};

}

#endif