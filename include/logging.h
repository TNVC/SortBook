/// @details Use next #define for declare log`s level:\n
/// LOG_LEVEL_NOTHING             - log nothing
/// LOG_LEVEL_ERROR               - log if was error
/// LOG_LEVEL_VALUE               - log every value
/// LOG_LEVEL_MESSAGE             - log every message
/// LOG_LEVEL_ALL                 - log anything\n
/// LOG_LEVEL_NOTHING has bigger priority than LOG_ALL\n
/// Logging to logFile

#ifndef LOG_FILE_NAME
#define LOG_FILE_NAME "logFile.txt"
#endif

#ifndef LOGGING_H_
#define LOGGING_H_

#include <stdio.h>
#include <stdarg.h>

#define INFO __FILE__, __PRETTY_FUNCTION__, __LINE__

#if not defined NOT_DEBUG_MODE_

#define LOG_MESSAGE(message)                                                                                        \
    {                                                                                                               \
        if (logLevel & LOG_MESSAGE)                                                                                 \
            fprintf(logFile, "Message : %36s, %28s File: %60s, Function: %120s, Line: %10d\n",                      \
                    message, "", INFO);                                                                             \
    }

#define LOG_POINTER(pointer)                                                                                        \
    {                                                                                                               \
        if (logLevel & LOG_VALUE)                                                                                   \
            fprintf(logFile, "Pointer : %36s, Value: %20p, File: %60s, Function: %120s, Line: %10d\n",              \
                    #pointer, pointer, INFO);                                                                       \
    }

#define LOG_DECIMAL(decimal)                                                                                        \
    {                                                                                                               \
        if (logLevel & LOG_VALUE)                                                                                   \
            fprintf(logFile, "Decimal : %36s, Value: %20lld, File: %60s, Function: %120s, Line: %10d\n",            \
                    #decimal, decimal, INFO);                                                                       \
    }

#define LOG_ERROR(expression)                                                                                       \
    {                                                                                                               \
        if (logLevel & LOG_ERROR)                                                                                   \
            fprintf(logFile, "ERROR!! Expression: %36s, File: %60s, Function: %120s, Line: %10d\n",                 \
                    #expression, INFO);                                                                             \
    }

#define LOG_POINTER_INDEX(pointer, i)                                                                               \
    {                                                                                                               \
        if (logLevel & LOG_VALUE)                                                                                   \
            fprintf(logFile, "Pointer: %20s, i = %10zd, Value: %20p, File: %60s, Function: %120s, Line: %10d\n",    \
                    #pointer, i, pointer, INFO);                                                                    \
    }

#define LOG_DECIMAL_INDEX(decimal, i)                                                                               \
    {                                                                                                               \
        if (logLevel & LOG_VALUE)                                                                                   \
            fprintf(logFile, "Decimal: %20s, i = %10zd, Value: %20lld, File: %60s, Function: %120s, Line: %10d\n",  \
                    #decimal, i, decimal, INFO);                                                                    \
    }

#define LOG_ERROR_INDEX(expression, i)                                                                              \
    {                                                                                                               \
        if (logLevel & LOG_ERROR)                                                                                   \
            fprintf(logFile, "ERROR!! Expression: %20s, i = %10zd, File: %60s, Function: %120s, Line: %10d\n",      \
                    #expression, i, INFO);                                                                          \
    }

#define LOG_LINE LOG_MESSAGE("STEP")

#else

#define LOG_MESSAGE(message)             ;
#define LOG_POINTER(pointer)             ;
#define LOG_FUNCTION(function)           ;
#define LOG_DECIMAL(decimal)             ;
#define LOG_ERROR(expression)            ;
#define LOG_POINTER_INDEX(pointer, i)    ;
#define LOG_FUNCTION_INDEX(function, i)  ;
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
extern FILE *logFile;

/// Variable for saving log level
extern int logLevel;

/// Init all for logging
/// @param [in] fileName Name of file
/// @return logLevel value
/// @note NULL equals standard log file
int initLog(const char *fileName);

/// Clean taken resource for logging\n
/// Use after all using log functions
void destroyLog();

#endif
