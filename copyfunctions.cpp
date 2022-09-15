#include <stdlib.h>
#include <string.h>
#include "line.h"
#include "copyfunctions.h"
#include "asserts.h"

String *getStringArray(char *buffer, size_t size, size_t *lines)
{
    pointerAssert(buffer, nullptr);
    pointerAssert(lines,  nullptr);

    *lines = 0;

    char *lastFindChar = buffer;

    while ((lastFindChar = strchr(lastFindChar, '\n')) != nullptr)
    {
        ++(*lines);

        #if defined OS_WINDOWS_

        *(lastFindChar - 1) = '\0';

        #endif

        *lastFindChar       = '\0';

        ++lastFindChar;

        if (lastFindChar >= buffer + size)
            break;
    }

    String *strings = (String *) calloc(*lines, sizeof(String));

    if (strings == nullptr)
        return nullptr;

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

    return strings;
}
