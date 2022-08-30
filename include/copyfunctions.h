#ifndef COPYFUNCTIONS_H_
#define COPYFUNCTIONS_H_

#include "line.h"

/// Split buffer to String array
/// @param [in] buffer Buffer with Strings
/// @param [in] size Size of  buffer
/// @param [out] lines Count of lines in file
/// @return Address in heap of String array or NULL if was error
String *getStringArray(char *buffer, size_t size, size_t *lines);

#endif
