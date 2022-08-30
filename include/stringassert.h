#if !(defined STRINGASSERT_H_) && !(defined NOT_DEBUG_MODE_)
#define STRINGASSERT_H_

#include <stdio.h>
#include <stdlib.h>

#define stringAssert(expression, i)                                                   \
    if (!(expression))                                                                \
    {                                                                                 \
        printf("Fail in %s. File: %s, Function: %s, Line: %d, Iteration: %zd\n",      \
              #expression, __FILE__, __PRETTY_FUNCTION__, __LINE__, i);               \
        abort();                                                                      \
    }

#endif

