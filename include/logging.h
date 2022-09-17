/// @details Use next #define for declare log`s level:\n
/// LOG_LEVEL_NOTHING             - log nothing
/// LOG_LEVEL_ERROR               - log if was error
/// LOG_LEVEL_VALUE               - log every value
/// LOG_LEVEL_MESSAGE             - log every message
/// LOG_LEVEL_ALL                 - log anything\n
/// LOG_LEVEL_NOTHING has bigger priority than LOG_ALL\n
/// Logging to logFile

#ifndef LOG_FILE_NAME
#define LOG_FILE_NAME "logFileTemp.txt"
#endif

#ifndef LOGGING_H_
#define LOGGING_H_

#include <stdio.h>
#include <stdarg.h>
#include "stacktrace.h"

#define INFO_FOR_LOG __FILE__, __PRETTY_FUNCTION__, __LINE__

#if not defined NOT_DEBUG_MODE_

#define LOG_MESSAGE(message)                                                                                        \
    {                                                                                                               \
        if (LogLevel & LOG_MESSAGE)                                                                                 \
            fprintf(LogFile, "Message : %36s, %28s File: %60s, Function: %120s, Line: %10d\n",                      \
                    message, "", INFO_FOR_LOG);                                                                     \
    }

#define LOG_POINTER(pointer)                                                                                        \
    {                                                                                                               \
        if (LogLevel & LOG_VALUE)                                                                                   \
            fprintf(LogFile, "Pointer : %36s, Value: %20p, File: %60s, Function: %120s, Line: %10d\n",              \
                    #pointer, pointer, INFO_FOR_LOG);                                                               \
    }

#define LOG_DECIMAL(decimal)                                                                                        \
    {                                                                                                               \
        if (LogLevel & LOG_VALUE)                                                                                   \
            fprintf(LogFile, "Decimal : %36s, Value: %20lld, File: %60s, Function: %120s, Line: %10d\n",            \
                    #decimal, decimal, INFO_FOR_LOG);                                                               \
    }

#define LOG_ERROR(expression)                                                                                       \
    {                                                                                                               \
        if (LogLevel & LOG_ERROR)                                                                                   \
            fprintf(LogFile, "ERROR!! Expression: %36s, File: %60s, Function: %120s, Line: %10d\n",                 \
                    #expression, INFO_FOR_LOG);                                                                     \
    }

#define LOG_POINTER_INDEX(pointer, i)                                                                               \
    {                                                                                                               \
        if (LogLevel & LOG_VALUE)                                                                                   \
            fprintf(LogFile, "Pointer: %20s, i = %10zd, Value: %20p, File: %60s, Function: %120s, Line: %10d\n",    \
                    #pointer, i, pointer, INFO_FOR_LOG);                                                            \
    }

#define LOG_DECIMAL_INDEX(decimal, i)                                                                               \
    {                                                                                                               \
        if (LogLevel & LOG_VALUE)                                                                                   \
            fprintf(LogFile, "Decimal: %20s, i = %10zd, Value: %20lld, File: %60s, Function: %120s, Line: %10d\n",  \
                    #decimal, i, decimal, INFO_FOR_LOG);                                                            \
    }

#define LOG_ERROR_INDEX(expression, i)                                                                              \
    {                                                                                                               \
        if (LogLevel & LOG_ERROR)                                                                                   \
            fprintf(LogFile, "ERROR!! Expression: %20s, i = %10zd, File: %60s, Function: %120s, Line: %10d\n",      \
                    #expression, i, INFO_FOR_LOG);                                                                  \
    }

#define LOG_LINE LOG_MESSAGE("STEP")

#else

#define LOG_MESSAGE(message)             ;
#define LOG_POINTER(pointer)             ;
#define LOG_DECIMAL(decimal)             ;
#define LOG_ERROR(expression)            ;
#define LOG_POINTER_INDEX(pointer, i)    ;
#define LOG_DECIMAL_INDEX(decimal, i)    ;
#define LOG_ERROR_INDEX(expression, i)   ;

#define LOG_LINE ;

#endif

///Log level codes for logging
enum {
    LOG_NOTHING = 0x00,
    LOG_ERROR   = 0x01 << 0,
    LOG_VALUE   = 0x01 << 1,
    LOG_MESSAGE = 0x01 << 2,
    LOG_ALL     = 0xFF,
};

/// Files for logging
extern FILE *LogFile;

/// Variable for saving log level
extern int LogLevel;

/// Init all for logging
/// @param [in] fileName Name of file
/// @return logLevel value
/// @note NULL equals standard log file
int initLog(const char *fileName);

/// Clean taken resource for logging\n
/// Use after all using log functions
void destroyLog();

#endif
