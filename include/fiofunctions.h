#ifndef FIOFUNCTIONS_H_
#define FIOFUNCTIONS_H_

#include <stddef.h>
#include "line.h"

/// Error`s codes from readAllLine()
enum {
    OUT_OF_MEM   = -1,
    FAIL_TO_OPEN = -2
};

/// Read every file line in buffer
/// @param [out] buffer Address of pointer to buffer
/// @param [in] filename Name of file which need to read
/// @return Size of buffer in heap
/// @note If was fail to open file return FAIL_TO_OPEN, if was error to allocate memory return OUT_OF_MEM
size_t readAllLines(char **buffer, const char *filename);

/// Write every line in file
/// @param [in] strings String array
/// @param [in] size Length of string array
/// @param [in] fileptr Output char stream
/// @note Every line must has '\\n'
void writeAllLines(String strings[], size_t size, FILE *fileptr);

/// Write buffer in file
/// @param [in] buffer Char buffer
/// @param [in] n Size of buffer
/// @param fileptr File
/// @note write '\\n' instead '\\0'
void writeBuffer(const char *buffer, size_t n, FILE *fileptr);

#endif
