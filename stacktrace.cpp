#include <stdlib.h>
#include "stacktrace.h"
#include "stack.h"

Stack StackTrace = {};

int IsStackTraceAvalible = initStackTrace();

int initStackTrace()
{
    initStack(&StackTrace);

    atexit(destroyStackTrace);

    return 1;
}

void destroyStackTrace()
{
    destroyStack(&StackTrace);

    IsStackTraceAvalible = 0;
}
