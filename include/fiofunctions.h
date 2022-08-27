#ifndef FIOFUNCTIONS_H_
#define FIOFUNCTIONS_H_

/// Read every line in file
/// @param [out] size Count of lines
/// @param [in] fileptr File which need to read
/// @return Array of string (each string - one line)
/// @note If was error return NULL
char **readAllLines(size_t *size, FILE *fileptr);

#endif
