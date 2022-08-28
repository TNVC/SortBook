#include <assert.h>
#include "copyfunctions.h"
#include "line.h"


String *getStringArray(const char *buffer, size_t lines)
{
    assert(buffer != nullptr);

    String *strings = (String *) calloc(lines, sizeof(String));

    if (strings == nullptr)
        return nullptr;

    size_t currentLine = 0;

    for (size_t i = 0; currentLine < lines; )
    {
        strings[currentLine++].value = buffer + i;

        while (buffer[i++])
            continue;
    }

    return strings;
}
