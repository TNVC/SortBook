#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include "fiofunctions.h"

/// Read chars while meat '\\n'
/// @details Function allocates memory in heap for string itself
/// and if need automatic resize (and if need reallocates) string in heap
///
/// @param [out] strPointer Pointer to read string
/// @param [out] n Pointer to length of read string
/// @param [in] stream Chars input stream
/// @return Count of chars in string with '\\0' or EOF if was error
/// @note Read '\\0' too
/// @note Don`t forget free() return address
static size_t getline(char **strPointer, size_t *n, FILE *stream);

char **readAllLines(size_t *size, FILE *fileptr)
{
    assert(size    != nullptr);
    assert(fileptr != nullptr);

    char **lines = nullptr;

    *size = 0;

    size_t linesSize = 16;
    lines = (char **) calloc(linesSize, sizeof(char *));

    if (lines == nullptr)
        return nullptr;

    size_t temp = 0;//remove it

    while (getline(&lines[(*size)++], &temp, fileptr) != (size_t) EOF)
        if (*size >= linesSize)
        {
            linesSize *= 2;

            lines = (char **) realloc(lines, linesSize * sizeof(char *));

            if (lines == nullptr)
            {
                *size = 0;

                return nullptr;
            }
        }

    lines = (char **) realloc(lines, *size * sizeof(char *));

    if (lines == nullptr)
    {
        *size = 0;

        return nullptr;
    }

    return lines;
}

static size_t getline(char **strPointer, size_t *n, FILE *stream)
{
    assert(strPointer != nullptr);
    assert(n          != nullptr);
    assert(stream     != nullptr);

    size_t size = 16;
    *strPointer = (char *) calloc(size, sizeof(char));

    int ch = 0;

    for (*n = 0; ch != '\n'; ++(*n))
    {
        if (*n >= size)
        {
            size *= 2;

            *strPointer = (char *) realloc(*strPointer, size);

            if (*strPointer == nullptr)
            {
                *n = 0;

                return (size_t) EOF;
            }
        }

        ch = getc(stream);

        if (ch == EOF)
        {
            (*strPointer)[(*n)++] = '\0';

            *strPointer = (char *) realloc(*strPointer, *n);

            if (*strPointer == nullptr)
            {
                *n = 0;

                return (size_t) EOF;
            }

            return (size_t) EOF;
        }

        (*strPointer)[*n] = (char) ch;
    }

    (*strPointer)[(*n)++] = '\0';

    *strPointer = (char *) realloc(*strPointer, *n);

    if (*strPointer == nullptr)
    {
        *n = 0;

        return (size_t) EOF;
    }

    return *n;
}

void writeAllLines(char *strings[], size_t size, FILE *fileptr)
{
    assert(strings != nullptr);
    assert(fileptr != nullptr);

    for (size_t i = 0; i < size; ++i)
        assert(strings[i] != nullptr);

    for (size_t i = 0; i < size; ++i)
        fprintf(fileptr, "%s", strings[i]);
}
