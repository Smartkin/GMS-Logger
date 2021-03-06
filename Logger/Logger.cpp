﻿// Logger.cpp : Defines Logger class functionality.
//

#include "stdafx.h"

std::string GetDateString();
CHAR* GetLibPath();

//Global _log object
Logger* _log = new Logger();

//Static _banned_symbols array
char Logger::banned_symb[9]{ '"', '\\', '/', ':', '|', '*', '<', '>', '?' };

Logger::Logger()
{
	_type = LogType::append;

	CHAR* path = GetLibPath();

	std::stringstream str;
	std::stringstream format_str;
	auto time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	format_str << std::put_time(std::localtime(&time), "%Y-%m-%d");
	std::string format(format_str.str());

	std::size_t found = format.find_first_of(banned_symb);
	while (found != std::string::npos)
	{
		format[found] = '/0';
		found = format.find_first_of(banned_symb, found + 1);
	}


	str << path;
	str << "Log_" << format;
	

	_file.open(str.str().c_str(), std::fstream::app | std::fstream::out);

	delete[] path;
}

Logger::Logger(LOGGER_TYPE type)
{
	_type = ParseLogType(type);
	if (_type == LogType::log_parse_failed)
		return;

	CHAR* path = GetLibPath();

	std::stringstream str;
	std::stringstream format_str;
	auto time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	format_str << std::put_time(std::localtime(&time), "%Y-%m-%d");
	std::string format(format_str.str());

	std::size_t found = format.find_first_of(banned_symb);
	while (found != std::string::npos)
	{
		format[found] = '/0';
		found = format.find_first_of(banned_symb, found + 1);
	}

	str << path;
	str << "Log_" << format;

	

	_file.open(str.str().c_str(), std::fstream::app | std::fstream::out);

	delete[] path;
}

Logger::Logger(const char* file)
{
	_type = LogType::append;

	CHAR* path = GetLibPath();

	std::stringstream str;
	str << path;
	str << file;

	_file.open(str.str().c_str(), std::fstream::app | std::fstream::out);

	delete[] path;
}

Logger::Logger(const char* file, LOGGER_TYPE type)
{
	_type = ParseLogType(type);
	if (_type == LogType::log_parse_failed)
		return;

	CHAR* path = GetLibPath();

	std::stringstream str;
	str << path;
	str << file;

	_file.open(str.str().c_str(), std::fstream::app | std::fstream::out);

	delete[] path;
}

Logger::~Logger()
{
	_file.close();
}

bool Logger::FileOpened()
{
	return _file.is_open();
}

RESULT Logger::Log(SEVERITY_LEVEL level, char* message)
{
	SeverityType sev_type = ParseSevType(level);
	if (sev_type == SeverityType::sev_parse_failed || !FileOpened())
		return FAILED;
	
	std::stringstream msg;

	if (_type & LogType::date)
		msg << GetDateString();

	if (_type & LogType::severity)
	{
		if (_type & LogType::date) msg << " ";

		switch (sev_type)
		{
		case SeverityType::debug:
			msg << "[DEBUG]";
			break;
		case SeverityType::error:
			msg << "[ERROR]";
			break;
		case SeverityType::information:
			msg << "[INFO]";
			break;
		case SeverityType::trace:
			msg << "[TRACE]";
			break;
		case SeverityType::warning:
			msg << "[WARN]";
			break;
		}
		msg << ": ";
	}
	msg << message << "\n";

	_file << msg.str();

	return SUCCESS;
}

RESULT Logger::SetMode(LOGGER_TYPE type)
{
	LogType new_type = ParseLogType(type);
	if (new_type == LogType::log_parse_failed)
		return FAILED;

	this->_type = new_type;
	return SUCCESS;
}

Logger::LogType Logger::ParseLogType(LOGGER_TYPE type)
{
	int int_type = (int)type;

	if (int_type < 1 || int_type > LogType::all)
	{
		std::wstringstream stream;
		stream << L"Logger mode parse for value " << int_type << " failed! You have to reinit the logger now!";
		MessageBox(NULL, stream.str().c_str(), L"Parse error!", MB_OK | MB_ICONWARNING);
		return LogType::log_parse_failed;
	}

	return (LogType)int_type;
}

Logger::SeverityType Logger::ParseSevType(SEVERITY_LEVEL level)
{
	int int_level = (int)level;

	if (level < 0 || level > SeverityType::TOTAL - 1)
	{
		std::wstringstream stream;
		stream << L"Severity type parse for value " << int_level << " failed! Try again!";
		MessageBox(NULL, stream.str().c_str(), L"Parse error!", MB_OK | MB_ICONWARNING);
		return SeverityType::sev_parse_failed;
	}

	return (SeverityType)int_level;
}

std::string GetDateString()
{
	std::stringstream str;
	auto time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	str << std::put_time(std::localtime(&time), "%Y-%m-%d %X");

	return str.str();
}

CHAR* GetLibPath()
{
	CHAR* path = new CHAR[MAX_PATH];
	GetFullPathNameA("Logger.dll", MAX_PATH, path, NULL);
	CHAR* format_path = new CHAR[std::strlen(path) - 9]{ '\0' };
	std::strncpy(format_path, path, std::strlen(path) - 10);

	delete[] path;

	return format_path;
}
