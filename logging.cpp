#include <stdio.h>
#include <assert.h>
#include <stdarg.h>
#include "logging.h"

/// Default file name
const char *defaultLogFileName = "logFile.txt";

/// For extern link declaration
int fileCount = 0;

/// For extern link declaration
FILE **logFiles = nullptr;

/// For extern link declaration
int logLevel = 0;

void initLog(int nFile, ...)
{
    va_list files;/// Not init

    va_start(files, nFile);

    fileCount = nFile;

    logFiles = (FILE **) calloc(nFile, sizeof(FILE *));

    if (logFiles == nullptr)
    {
        logLevel = 0x00;

        va_end(files);

        return;
    }

    for (int i = 0; i < nFile; ++i)
    {
        logFiles[i] = va_arg(files, FILE *);

        if (logFiles[i] == nullptr)/// Only one
            logFiles[i] = fopen(defaultLogFileName, "w");
    }

    va_end(files);

    #if defined(LOG_LEVEL_ERROR)

        logLevel |= LOG_ERROR;

    #endif

    #if defined(LOG_LEVEL_VALUE)

        logLevel |= LOG_VALUE;

    #endif

    #if defined(LOG_LEVEL_MESSAGE)

        logLevel |= LOG_MESSAGE;

    #endif

    #if defined(LOG_LEVEL_ALL)

        logLevel |= LOG_ALL;

    #endif

    #if defined(LOG_LEVEL_NOTHING)

        logLevel |= LOG_NOTHING;

    #endif
}

void destroyLog()
{
    for (int i = 0; i < fileCount; ++i)
        fclose(logFiles[i]);

    free(logFiles);
}

void logPointer(const char *expression, ssize_t index, const void *pointer, const char *fileName, const char *functionName, int lineNum)
{
    assert(expression   != nullptr);
    assert(fileName     != nullptr);
    assert(functionName != nullptr);
    assert(lineNum > 0);

    if (!(logLevel & LOG_VALUE))
        return;

    if (index < 0)
        for (int i = 0; i < fileCount; ++i)
            fprintf(logFiles[i], "Pointer: %36s, Value: %20p, File: %60s, Function: %120s, Line: %10d\n",
                    expression, pointer, fileName, functionName, lineNum);
    else
        for (int i = 0; i < fileCount; ++i)
            fprintf(logFiles[i], "Pointer: %25s %10zd, Value: %20p, File: %60s, Function: %120s, Line: %10d\n",
                    expression, index, pointer, fileName, functionName, lineNum);
}

void logDecimal(const char *expression, ssize_t index, ssize_t value, const char *fileName, const char *functionName, int lineNum)
{
    assert(expression   != nullptr);
    assert(fileName     != nullptr);
    assert(functionName != nullptr);
    assert(lineNum > 0);

    if (!(logLevel & LOG_VALUE))
        return;

    if (index < 0)
        for (int i = 0; i < fileCount; ++i)
            fprintf(logFiles[i], "Decimal: %36s, Value: %20zd, File: %60s, Function: %120s, Line: %10d\n",
                    expression, value, fileName, functionName, lineNum);
    else
        for (int i = 0; i < fileCount; ++i)
            fprintf(logFiles[i], "Decimal: %25s %10zd, Value: %20zd, File: %60s, Function: %120s, Line: %10d\n",
                    expression, index, value, fileName, functionName, lineNum);
}

void logError(const char *expression, ssize_t index, const char *fileName, const char *functionName, int lineNum)
{
    assert(expression   != nullptr);
    assert(fileName     != nullptr);
    assert(functionName != nullptr);
    assert(lineNum > 0);

    if (!(logLevel & LOG_ERROR))
        return;

    if (index < 0)
        for (int i = 0; i < fileCount; ++i)
            fprintf(logFiles[i], "ERROR!! Expression: %36s, File: %60s, Function: %120s, Line: %10d\n",
                    expression, fileName, functionName, lineNum);
    else
        for (int i = 0; i < fileCount; ++i)
            fprintf(logFiles[i], "ERROR!! Expression: %25s %10zd, File: %60s, Function: %120s, Line: %10d\n",
                    expression, index, fileName, functionName, lineNum);
}

void logMessage(const char *message, const char *fileName, const char *functionName, int lineNum)
{
    assert(message      != nullptr);
    assert(fileName     != nullptr);
    assert(functionName != nullptr);
    assert(lineNum > 0);

    if (!(logLevel & LOG_MESSAGE))
        return;

    for (int i = 0; i < fileCount; ++i)
        fprintf(logFiles[i], "Message: %120s, File: %60s, Function: %120s, Line: %10d\n",
                message, fileName, functionName, lineNum);
}
