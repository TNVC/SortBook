#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "stacktrace.h"
#include "stack.h"

Stack StackTrace = {};

int IsStackTraceAvailable = initStackTrace();

int initStackTrace()
{
    initStack(&StackTrace);

    atexit(destroyStackTrace);

    return 1;
}

void destroyStackTrace()
{
    destroyStack(&StackTrace);

    IsStackTraceAvailable = 0;
}


void stackTracePrint(const Stack *stk, FILE *filePtr)
{
    assert(stk     != nullptr);
    assert(filePtr != nullptr);

    size_t i = stk->size;

    fprintf(filePtr, "=========================STACK_TRACE=========================\n");

    for (Node *node = stk->tail; node != nullptr; node = node->previous, --i)
    {
        StackTraceElement *temp = (StackTraceElement *)node->element;

        fprintf(filePtr, "#%zd %120s at %30s in line %4d\n",
                i, temp->functionName, temp->fileName, temp->line);
    }

    fprintf(filePtr, "=============================================================\n");
}

void copyElement(void *target, const void *source)
{
    assert(target != nullptr);
    assert(source != nullptr);

    memcpy(target, source, sizeof(StackTraceElement));
}
