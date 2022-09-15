#ifndef HEAP_FUNCTIONS_
#define HEAP_FUNCTIONS_

#include "line.h"

/// Struct for work with text from file
typedef struct {
    char   *originBuffer;///<- File-buffer
    size_t size;         ///<- Size of originBuffer
    String *sequence;    ///<- Current sequence of string
    size_t stringCount;  ///<- Count of strings in sequence
} Strings;

///Init strings
///@param [out] strings Struct with info about text from file
///@note Need to call before all using strings
void constructor(Strings *strings);

///Destroy strings
///@param [in] strings Struct with info about text from file
///@note Need to call after all using strings
void destructor(Strings *strings);

#endif
