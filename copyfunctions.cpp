#include <stdlib.h>
#include <string.h>
#include "line.h"
#include "copyfunctions.h"
#include "asserts.h"

static size_t splitBuff(char *buffer, size_t size);

String *getStringArray(char *buffer, size_t size, size_t *lines)
{
    FUNC_START;

    pointerAssert(buffer, nullptr);
    pointerAssert(lines,  nullptr);

    LOG_LINE;

    *lines = splitBuff(buffer, size);

    String *strings = (String *) calloc(*lines, sizeof(String));

    if (strings == nullptr)
        RETURN(nullptr);

    size_t currentLine = 0, lineSize = 0;

    for (size_t i = 0; currentLine < *lines; )
    {
        strings[currentLine].buff  = buffer + i;

        while (buffer[i++] != '\0')
            ++lineSize;

        strings[currentLine++].size = lineSize;

        lineSize = 0;

        #if defined OS_WINDOWS_

        ++i;

        #endif
    }

    RETURN(strings);
}

static size_t splitBuff(char *buffer, size_t size)
{
    FUNC_START;

    pointerAssert(buffer, nullptr);

    size_t lines = 0;

    char *lastFindChar = buffer;

    while ((lastFindChar = strchr(lastFindChar, '\n')) != nullptr)
    {
        ++lines;

        #if defined OS_WINDOWS_

        *(lastFindChar - 1) = '\0';

        #endif

        *lastFindChar       = '\0';

        ++lastFindChar;

        if (lastFindChar >= buffer + size)
            break;
    }

    RETURN(lines);
}
