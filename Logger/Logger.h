#pragma once
#include<fstream>
#include<string>
#include<functional>

#define EXPORT extern "C" __declspec(dllexport)

//Gamemaker requires for function to return double/string
//Return either to indicate whether function failed or succeeded
#ifndef FLAGS_DEF
#define FLAGS_DEF
#define SUCCESS 0.0
#define FAILED 1.0
#define LOG_PARSE_ERROR -1.0
#define SEV_PARSE_ERROR -2.0
typedef double RESULT;
typedef double SEVERITY_LEVEL;
typedef double LOGGER_TYPE;
#endif

class Logger
{
private:
#pragma region ENUMS

	enum LogType
	{
		log_parse_failed = (int)LOG_PARSE_ERROR,

		append		= 1 << 0,
		date		= 1 << 1,
		severity	= 1 << 2,

		all			= 1 << 3
	};

	enum SeverityType
	{
		sev_parse_failed = (int)SEV_PARSE_ERROR,

		trace = 0,
		information,
		debug,
		warning,
		error,

		TOTAL
	};

#pragma endregion

public:
	Logger();
	Logger(const char* file);
	Logger(LOGGER_TYPE type);
	Logger(const char* file, LOGGER_TYPE type);

	~Logger();

	RESULT Log(SEVERITY_LEVEL level, char* message);

	RESULT SetMode(LOGGER_TYPE type);

	bool FileOpened();

private:
	LogType ParseLogType(LOGGER_TYPE type);
	SeverityType ParseSevType(SEVERITY_LEVEL level);


private:
	std::fstream _file;
	LogType _type;

public:
	static char banned_symb[];
};

extern Logger* _log;