#ifndef COPYFUNCTIONS_H_
#define COPYFUNCTIONS_H_

#include <stdlib.h>

/// Free every string in array and array from heap
/// @param [in] strings Array of strings
/// @param [in] n Array length
void cleanStringArray(char *strings[], size_t n);

/// Copy string array in heap
/// @param [in] strings Source array of strings
/// @param [in] n Size of array
/// @param [out] new_size Size of copy array
/// @return Address of copy or NULL if was error
char **copyStringArray(char *strings[], size_t n, size_t *new_size);

#endif
