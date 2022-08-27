#ifndef COPYFUNCTIONS_H_
#define COPYFUNCTIONS_H_

#include <stdlib.h>

/// Free every string in array and array from heap
/// @param [in] strings Array of strings
/// @param [in] n Array length
void cleanStringArray(char *strings[], size_t n);

#endif
