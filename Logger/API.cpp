// API.cpp : Defines the exported functions for the DLL application.
// Due to GameMaker: Studio's contraints on externals
// all API has to be defined globally.

#include "stdafx.h"

EXPORT RESULT InitLoggerType(LOGGER_TYPE type)
{
	if (_log)
		delete _log;

	_log = new Logger(type);

	auto res = SUCCESS;
	if (!_log || !_log->FileOpened())
	{
		res = FAILED;
		if (!_log->FileOpened())
			delete _log;
	}

	return res;
}

EXPORT RESULT InitLogger()
{
	return InitLoggerType(1 << 0);
}

EXPORT RESULT InitLoggerTypeName(LOGGER_TYPE type, char* file_name)
{
	if (_log)
		delete _log;

	_log = new Logger(file_name, type);

	std::string check_name(file_name);

	auto res = SUCCESS;
	if (!_log || !_log->FileOpened() || check_name.find_first_of(Logger::banned_symb))
	{
		res = FAILED;
		if (!_log->FileOpened())
			delete _log;
	}

	return res;
}

EXPORT RESULT InitLoggerName(char* file_name)
{
	return InitLoggerTypeName(1 << 0, file_name);
}

EXPORT RESULT Log(SEVERITY_LEVEL level, char* message)
{
	if (_log)
		return _log->Log(level, message);
	return FAILED;
}