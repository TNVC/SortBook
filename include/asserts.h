#ifndef ASSERTS_H_
#define ASSERTS_H_

#include <stdio.h>
#include <stdlib.h>
#include "logging.h"

#if not defined NOT_DEBUG_MODE_

#define indexAssert(expression, i)                                                    \
    if (!(expression))                                                                \
    {                                                                                 \
        logError(ERROR_ARRAY_INFO(expression, i));                                    \
                                                                                      \
        abort();                                                                      \
    }

#define arrayPointerAssert(array, badValue, size)                                     \
    for (int i = 0; i < size; ++i)                                                    \
    {                                                                                 \
        indexAssert((array)[i] != badValue, i)                                        \
                                                                                      \
        logPointer(LOG_ARRAY_INFO((array)[i], i));                                    \
    }

#define arrayDecimalAssert(array, badValue, size)                                     \
    for (int i = 0; i < size; ++i)                                                    \
    {                                                                                 \
        indexAssert((array)[i] != badValue, i)                                        \
                                                                                      \
        logDecimal(LOG_ARRAY_INFO((array)[i], i));                                    \
    }

#define pointerAssert(pointerValue, badPointerValue)                                  \
    {                                                                                 \
        assert(pointerValue != badPointerValue);                                      \
                                                                                      \
        logPointer(LOG_INFO(pointerValue));                                           \
    }

#define functionAssert(functionValue, badFunctionValue)                               \
    {                                                                                 \
        assert(functionValue != badFunctionValue);                                    \
                                                                                      \
        logPointer(LOG_FUNCTION_INFO(functionValue));                                 \
    }

#define decimalAssert(decimalValue, badDecimalValue)                                  \
    {                                                                                 \
        assert(decimalValue != badDecimalValue);                                      \
                                                                                      \
        logDecimal(LOG_INFO(decimalValue));                                           \
    }

#define pointerIndexAssert(pointerValue, badPointerValue, i)                          \
    {                                                                                 \
        indexAssert(pointerValue != badPointerValue, i);                              \
                                                                                      \
        logPointer(LOG_ARRAY_INFO(pointerValue, i));                                  \
    }

#define decimaIndexlAssert(decimalValue, badDecimalValue, i)                          \
    {                                                                                 \
        indexAssert(decimalValue != badDecimalValue, i);                              \
                                                                                      \
        logDecimal(LOG_ARRA_INFO(decimalValue));                                      \
    }

#define assert(expression)                                                          \
    if (!(expression))                                                              \
    {                                                                               \
        logError(ERROR_INFO(expression));                                           \
                                                                                    \
        abort();                                                                    \
    }

#else

#define arrayAssert(expression, i) ;

#define arrayPointerAssert(array, badValue, size) ;

#define arrayDecimalAssert(array, badValue, size) ;

#define pointerAssert(pointerValue, badPointerValue) ;

#define functionAssert(functionValue, badFunctionValue) ;

#define decimalAssert(decimalValue, badDecimalValue) ;

#define pointerIndexAssert(pointerValue, badPointerValue, i) ;

#define decimaIndexlAssert(decimalValue, badDecimalValue, i) ;

#define assert(expression) ;

#endif

#endif

