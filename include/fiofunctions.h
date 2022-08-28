#ifndef FIOFUNCTIONS_H_
#define FIOFUNCTIONS_H_

/// Read every line in file
/// @param [out] size Count of lines
/// @param [in] fileptr File which need to read
/// @return Array of string (each string - one line)
/// @note If was error return NULL
/// @note Every line has '\\n'
char **readAllLines(size_t *size, FILE *fileptr);

/// Write every line in file
/// @param [in] strings String array
/// @param [in] size Length of string array
/// @param [in] fileptr Outpur char stream
/// @note Every line must has '\\n'
void writeAllLines(char *strings[], size_t size, FILE *fileptr);

#endif
