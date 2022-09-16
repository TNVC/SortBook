#include <stdio.h>
#include <assert.h>
#include <stdarg.h>
#include <time.h>
#include "logging.h"

#define SEPARATOR "============================================="

/// For extern link declaration
FILE *logFile = nullptr;

/// For extern link declaration
int logLevel = initLog(LOG_FILE_NAME);

int initLog(const char *fileName)
{
    if (fileName == nullptr)
        logFile = fopen(LOG_FILE_NAME, "a");
    else
        logFile = fopen(fileName     , "a");

    if (logFile == nullptr)
        return 0x00;

    setvbuf(logFile, nullptr, _IOFBF, 0);

    fprintf(logFile, SEPARATOR         SEPARATOR "\n");
    {
        time_t now = 0;

        time(&now);

        fprintf(logFile, ctime(&now));
    }
    fprintf(logFile, SEPARATOR "START" SEPARATOR "\n\n");
    fprintf(logFile, SEPARATOR         SEPARATOR "\n");

    atexit(destroyLog);

    int level = 0;

    #if defined(LOG_LEVEL_ERROR)

        level |= LOG_ERROR;

    #endif

    #if defined(LOG_LEVEL_VALUE)

        level |= LOG_VALUE;

    #endif

    #if defined(LOG_LEVEL_MESSAGE)

        level |= LOG_MESSAGE;

    #endif

    #if defined(LOG_LEVEL_ALL)

        level |= LOG_ALL;

    #endif

    #if defined(LOG_LEVEL_NOTHING)

        level |= LOG_NOTHING;

    #endif

    return level;
}

void destroyLog()
{

    fprintf(logFile, SEPARATOR       SEPARATOR "\n\n");
    fprintf(logFile, SEPARATOR "END" SEPARATOR "\n\n");
    fprintf(logFile, SEPARATOR       SEPARATOR "\n");

    fclose(logFile);
}
