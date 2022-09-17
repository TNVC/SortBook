#ifndef STACKTRACE_H_
#define STACKTRACE_H_

#include <stdio.h>
#include "stack.h"

#define INFO_FOR_STACKTRACE __PRETTY_FUNCTION__, __FILE__, __LINE__

#if not defined NOT_DEBUG_MODE_

#define RETURN(value)                                                                       \
    {                                                                                       \
        FUNC_END;                                                                           \
                                                                                            \
        return value;                                                                       \
    }

#define RETURN_ FUNC_END;

#define FUNC_START                                                                          \
    {                                                                                       \
        StackTraceElement stackTraceTemp = {INFO_FOR_STACKTRACE};                           \
                                                                                            \
        stack_push(&StackTrace, &stackTraceTemp, sizeof(StackTraceElement), copyElement);   \
    }

#define FUNC_END                                                                            \
    {                                                                                       \
        StackTraceElement stackTraceTemp = {};                                              \
                                                                                            \
        stack_pop(&StackTrace, &stackTraceTemp, copyElement);                               \
    }

#define PRINT_STACK_TRACE stackTracePrint(&StackTrace, LogFile)

#else

#define RETURN(value) return value
#define RETURN_       return
#define FUNC_START        ;
#define FUNC_END          ;
#define PRINT_STACK_TRACE ;

#endif

typedef struct element {
    const char *functionName;
    const char *fileName;
    int line;
} StackTraceElement;

/// Stack for stackTrace
extern Stack StackTrace;

/// StackTrace is available
extern int IsStackTraceAvailable;

/// Init StackTrace
int initStackTrace();

/// Destroy StackTrace
void destroyStackTrace();

/// Print StackTrace into filePtr
/// @param [in] stk Stack to print
/// @param [in] filePtr File for print
void stackTracePrint(const Stack *stk, FILE *filePtr);

/// Copy function for stack functions
void copyElement(void *target, const void *source);

#endif
