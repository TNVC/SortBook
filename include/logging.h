/// @details Use next #define for declare log`s level:\n
/// LOG_LEVEL_NOTHING             - log nothing
/// LOG_LEVEL_ERROR               - log if was error
/// LOG_LEVEL_VALUE               - log every value
/// LOG_LEVEL_MESSAGE             - log every message
/// LOG_LEVEL_ALL                 - log anything\n
/// LOG_LEVEL_NOTHING has bigger priority than LOG_ALL\n
/// Logging to all files in logFiles

#ifndef LOGGING_H_
#define LOGGING_H_

#include <stdio.h>
#include <stdarg.h>

/// Use for all call log function
#define LOG_INFO(value)             #value,         -1, (value),         __FILE__, __PRETTY_FUNCTION__, __LINE__
#define ERROR_INFO(value)           #value,         -1,                  __FILE__, __PRETTY_FUNCTION__, __LINE__
#define LOG_FUNCTION_INFO(value)    #value,         -1, (void *)(value), __FILE__, __PRETTY_FUNCTION__, __LINE__
#define LOG_ARRAY_INFO(value, i)    #value ", i = ", i, (value),         __FILE__, __PRETTY_FUNCTION__, __LINE__
#define ERROR_ARRAY_INFO(value, i)  #value ", i = ", i,                  __FILE__, __PRETTY_FUNCTION__, __LINE__
#define LOG_MESSAGE(message)        message,                             __FILE__, __PRETTY_FUNCTION__, __LINE__

///Log level codes for logging
enum {
    LOG_NOTHING = 0x00,
    LOG_ERROR   = 0x01 << 0,
    LOG_VALUE   = 0x01 << 1,
    LOG_MESSAGE = 0x01 << 2,
    LOG_ALL     = 0xFF,
};

/// Count of files for logging
extern int fileCount;

/// Files for logging
extern FILE **logFiles;

/// Variable for saving log level
extern int logLevel;

/// Init all for logging\n
/// Use before all using log functions
/// @param [in] nFile Count of file
/// @param [in] ... Sequence of file  to logging
/// @note NULL equals standard log file
void initLog(int nFile, ...);

/// Clean taken resource for logging\n
/// Use after all using log functions
void destroyLog();

/// Log pointer value
/// @param [in] expression Name of pointer-value
/// @param [in] index Index of object if it has it
/// @param [in] pointer Value of pointer
/// @param [in] fileName Name of file where was call logPointer()
/// @param [in] functionName Name of function where was call logPointer()
/// @param [in] lineNum Number of line where was call logPointer()
/// @note If index == -1 than index will be ignore
void logPointer(const char *expression, ssize_t index, const void *pointer, const char *fileName, const char *functionName, int lineNum);

/// Log decimal value
/// @param [in] expression Name of decimal-value
/// @param [in] index Index of object if it has it
/// @param [in] value Value of decimal
/// @param [in] fileName Name of file where was call logDecimal()
/// @param [in] functionName Name of function where was call logDecimal()
/// @param [in] lineNum Number of line where was call logDecimal()
/// @note If index == -1 than index will be ignore
void logDecimal(const char *expression, ssize_t index, ssize_t value, const char *fileName, const char *functionName, int lineNum);

/// Log error
/// @param [in] expression Name of error
/// @param [in] index Index of object if it has it
/// @param [in] fileName Name of file where was call logError()
/// @param [in] functionName Name of function where was call logError()
/// @param [in] lineNum Number of line where was call logError()
/// @note If index == -1 than index will be ignore
void logError(const char *expression, ssize_t index, const char *fileName, const char *functionName, int lineNum);

/// Log message
/// @param [in] message Message to log
/// @param [in] fileName Name of file where was call logMessage()
/// @param [in] functionName Name of function where was call logMessage()
/// @param [in] lineNum Number of line where was call logMessage()
void logMessage(const char *message, const char *fileName, const char *functionName, int lineNum);

#endif
