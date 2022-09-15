#include <stdlib.h>
#include "heapfunctions.h"
#include "asserts.h"

void constructor(Strings *strings)
{
    pointerAssert(strings, nullptr);

    strings->originBuffer = nullptr;
    strings->size         = 0;
    strings->sequence     = nullptr;
    strings->stringCount  = 0;
}

void destructor(Strings *strings)
{
    pointerAssert(strings, nullptr);

    strings->size        = 0;
    strings->stringCount = 0;

    if (strings->originBuffer != nullptr)
        free(strings->originBuffer);
    if (strings->sequence     != nullptr)
        free(strings->sequence);
}
