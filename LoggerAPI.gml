#define scrInitLoggerFuncs
///scrInitLoggerFuncs()

enum LOG_MODE
{
    append = 1 << 0,
    date = 1 << 1,
    severity = 1 << 2
}

enum SEV_MODE
{
    trace,
    information,
    debug,
    warning,
    error
}

global._logInitFunc = external_define("Logger.dll","InitLogger",dll_cdecl,ty_real,0);
global._logInitTypeFunc = external_define("Logger.dll","InitLoggerType",dll_cdecl,ty_real,1,ty_real);
global._logInitNameFunc = external_define("Logger.dll","InitLoggerName",dll_cdecl,ty_real,1,ty_string);
global._logInitNameTypeFunc = external_define("Logger.dll","InitLoggerTypeName",dll_cdecl,ty_real,2,ty_real,ty_string);
global._logLogFunc = external_define("Logger.dll","Log",dll_cdecl,ty_real,2,ty_real,ty_string);

#define scrInitLogger
///scrInitLogger()

return external_call(global._logInitFunc);

#define scrInitLoggerName
///scrInitLoggerName(file_name)

return external_call(global._logInitNameFunc,argument0);

#define scrInitLoggerType
///scrInitLoggerType(mode)

return external_call(global._logInitTypeFunc,argument0);

#define scrInitLoggerTypeName
///scrInitLoggerTypeName(mode, file_name)

return external_call(global._logInitNameTypeFunc, argument0, argument1);

#define scrLog
///scrLog(severity_level,message)

return external_call(global._logLogFunc,argument0,argument1);

