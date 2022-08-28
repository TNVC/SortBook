#ifndef COPYFUNCTIONS_H_
#define COPYFUNCTIONS_H_

#include "line.h"

/// Split buffer to String array
/// @param [in] buffer Buffer with Strings
/// @param [in] lines Count of lines in buffer
/// @return Address in heap of String arrayor NULL if was error
String *getStringArray(const char *buffer, size_t lines);

#endif
