#include <stdio.h>
#include <assert.h>
#include <stdarg.h>
#include <time.h>
#include "logging.h"

#define SEPARATOR "============================================="

/// For extern link declaration
FILE *LogFile = nullptr;

/// For extern link declaration
int LogLevel = initLog(LOG_FILE_NAME);

int initLog(const char *fileName)
{
    if (fileName == nullptr)
        LogFile = fopen(LOG_FILE_NAME, "a");
    else
        LogFile = fopen(fileName     , "a");

    if (LogFile == nullptr)
        return 0x00;

    setvbuf(LogFile, nullptr, _IOFBF, 0);

    fprintf(LogFile, SEPARATOR         SEPARATOR "\n");
    {
        time_t now = 0;

        time(&now);

        fprintf(LogFile, "%s", ctime(&now));
    }
    fprintf(LogFile, SEPARATOR "START" SEPARATOR "\n\n");
    fprintf(LogFile, SEPARATOR         SEPARATOR "\n");

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
    fprintf(LogFile, SEPARATOR       SEPARATOR "\n\n");
    fprintf(LogFile, SEPARATOR "END" SEPARATOR "\n\n");
    fprintf(LogFile, SEPARATOR       SEPARATOR "\n");

    fclose(LogFile);
}
