#include <stdlib.h>
#include "heapfunctions.h"
#include "asserts.h"

void constructor(Strings *strings)
{
    FUNC_START;

    pointerAssert(strings, nullptr);

    LOG_LINE;

    strings->originBuffer = nullptr;
    strings->size         = 0;
    strings->sequence     = nullptr;
    strings->stringCount  = 0;

    RETURN_;
}

void destructor(Strings *strings)
{
    FUNC_START;

    pointerAssert(strings, nullptr);

    strings->size        = 0;
    strings->stringCount = 0;

    LOG_LINE;

    free(strings->originBuffer);
    free(strings->sequence);

    RETURN_;
}
