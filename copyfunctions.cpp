#include "copyfunctions.h"

void cleanStringArray(char *strings[], size_t n)
{
    for (size_t i = 0; i < n; ++i)
        free(strings[i]);

    free(strings);
}
