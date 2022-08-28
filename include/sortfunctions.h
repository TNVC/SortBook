#ifndef SORTFUNCTIONS_H_
#define SORTFUNCTIONS_H_

#include "line.h"

/// Sort string array
/// @param [in/out] strings Array of string
/// @param [in] n Size of string array
/// @param [in] funcptr Comparator function
/// @return Address of strings
String *sortStringArray(String strings[], size_t n, int (*funcptr)(const void *first, const void *second));

/// String comparator for "qsort()"
/// @param [in] first First sting to compare
/// @param [in] second Second string to compare
/// @return 0 if first equals two, positive if first more than second and negative if first less than second
int stringComparator(const void *first, const void *second);

/// Reverse string comparator for "qsort()"
/// @param [in] first First sting to compare
/// @param [in] second Second string to compare
/// @return 0 if reverse first equals reverse two,\n
/// positive if reverse first more than reverse second and negative if reverse first less than reverse second
int reverseStringComparator(const void *first, const void *second);

#endif
