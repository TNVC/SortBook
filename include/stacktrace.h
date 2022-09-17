#ifndef STACKTRACE_H_
#define STACKTRACE_H_

#include <stdio.h>
#include "stack.h"
#include "logging.h"

#define INFO_FOR_STACKTRACE __PRETTY_FUNCTION__, __FILE__, __LINE__

#if not defined NOT_DEBUG_MODE_

#define FUNC_START                                                  \
    {                                                               \
        StackElement stackTraceTemp = {INFO_FOR_STACKTRACE};        \
                                                                    \
        stack_push(&StackTrace, &stackTraceTemp);                   \
    }

#define FUNC_END                                                    \
    {                                                               \
        StackElement stackTraceTemp = {};                           \
                                                                    \
        stack_pop(&StackTrace, &stackTraceTemp);                    \
    }

#define PRINT_STACK_TRACE stack_print(&StackTrace, LogFile)

#else

#define FUNC_START        ;
#define FUNC_END          ;
#define PRINT_STACK_TRACE ;

#endif

extern Stack StackTrace;

extern int IsStackTraceAvalible;

int initStackTrace();

void destroyStackTrace();

#endif
