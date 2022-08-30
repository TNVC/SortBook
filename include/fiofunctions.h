#ifndef FIOFUNCTIONS_H_
#define FIOFUNCTIONS_H_

#include <stddef.h>
#include "line.h"

static const int OUT_OF_MEM = -1;

/// Read every file line in buffer
/// @param [out] buffer Address of pointer to buffer
/// @param [in] fileptr File which need to read in bin mode
/// @return Size of buffer in heap
/// @note If was error return OUT_OF_MEM
size_t readAllLines(char **buffer, FILE *fileptr);

/// Write every line in file
/// @param [in] strings String array
/// @param [in] size Length of string array
/// @param [in] fileptr Outpur char stream
/// @note Every line must has '\\n'
void writeAllLines(String strings[], size_t size, FILE *fileptr);

/// Write buffer in file
/// @param [in] buffer Char buffer
/// @param [in] n Size of buffer
/// @param fileptr File
/// @note write '\\n' instead '\\0'
void writeBuffer(const char *buffer, size_t n, FILE *fileptr);

#endif
