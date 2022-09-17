#ifndef ASSERTS_H_
#define ASSERTS_H_

#include <stdio.h>
#include <stdlib.h>
#include "logging.h"

#if not defined NOT_DEBUG_MODE_

#define indexAssert(expression, i)                                                    \
    if (!(expression))                                                                \
    {                                                                                 \
        LOG_ERROR_INDEX(expression, i);                                               \
                                                                                      \
        LogLevel = 0x00;                                                              \
                                                                                      \
        PRINT_STACK_TRACE;                                                            \
                                                                                      \
        destroyStackTrace();                                                          \
                                                                                      \
        abort();                                                                      \
    }

#define arrayPointerAssert(array, badValue, size)                                     \
    for (int i = 0; i < size; ++i)                                                    \
    {                                                                                 \
        indexAssert((array)[i] != badValue, i)                                        \
                                                                                      \
        LOG_POINTER_INDEX((array)[i], i);                                             \
    }

#define arrayDecimalAssert(array, badValue, size)                                     \
    for (int i = 0; i < size; ++i)                                                    \
    {                                                                                 \
        indexAssert((array)[i] != badValue, i)                                        \
                                                                                      \
        LOG_DECIMAL_INDEX((array)[i], i);                                             \
    }

#define pointerAssert(pointerValue, badPointerValue)                                  \
    {                                                                                 \
        assert(pointerValue != badPointerValue);                                      \
                                                                                      \
        LOG_POINTER(pointerValue);                                                    \
    }

#define decimalAssert(decimalValue, badDecimalValue)                                  \
    {                                                                                 \
        assert(decimalValue != badDecimalValue);                                      \
                                                                                      \
        LOG_DECIMAL(decimalValue);                                                    \
    }

#define pointerIndexAssert(pointerValue, badPointerValue, i)                          \
    {                                                                                 \
        indexAssert(pointerValue != badPointerValue, i);                              \
                                                                                      \
        LOG_POINTER_INDEX(pointerValue, i);                                           \
    }

#define decimaIndexlAssert(decimalValue, badDecimalValue, i)                          \
    {                                                                                 \
        indexAssert(decimalValue != badDecimalValue, i);                              \
                                                                                      \
        LOG_DECIMAL_INDEX(decimalValue, i);                                           \
    }

#define assert(expression)                                                            \
    if (!(expression))                                                                \
    {                                                                                 \
        LOG_ERROR(expression);                                                        \
                                                                                      \
        LogLevel = 0x00;                                                              \
                                                                                      \
        PRINT_STACK_TRACE;                                                            \
                                                                                      \
        destroyStackTrace();                                                          \
                                                                                      \
        abort();                                                                      \
    }

#else

#define arrayAssert(expression, i)                           ;
#define arrayPointerAssert(array, badValue, size)            ;
#define arrayDecimalAssert(array, badValue, size)            ;
#define pointerAssert(pointerValue, badPointerValue)         ;
#define decimalAssert(decimalValue, badDecimalValue)         ;
#define pointerIndexAssert(pointerValue, badPointerValue, i) ;
#define decimaIndexlAssert(decimalValue, badDecimalValue, i) ;
#define assert(expression)                                   ;

#endif

#endif

