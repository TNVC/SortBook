#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "fiofunctions.h"
#include "line.h"

/// Return file size
/// @param [in] fileptr File
/// @return Size of file in byte
static size_t getFileSize(FILE *fileptr);

size_t readAllLines(char **buffer, size_t *lines, FILE *fileptr)
{
    assert(buffer  != nullptr);
    assert(fileptr != nullptr);
    assert(lines   != nullptr);

    size_t size = getFileSize(fileptr);

    *buffer = (char *) calloc(size, sizeof(char));

    if (*buffer == nullptr)
        return (size_t) EOF;

    fread(*buffer, sizeof(char), size, fileptr);

    *lines = 0;

    for (size_t i = 0; i < size; ++i)
        if ((*buffer)[i] == '\n')
        {
            ++(*lines);

            #if defined OS_WINDOWS_

            (*buffer)[i - 1] = '\0';
            (*buffer)[i]     = '\0';

            #else

            (*buffer)[i]     = '\0';

            #endif
        }

    return size;
}

void writeAllLines(String strings[], size_t size, FILE *fileptr)
{
    assert(strings != nullptr);
    assert(fileptr != nullptr);

    for (size_t i = 0; i < size; ++i)
        assert(strings[i].value != nullptr);

    for (size_t i = 0; i < size; ++i)
        fprintf(fileptr, "%s\n", strings[i].value);
}

void writeBuffer(const char *buffer, size_t n, FILE *fileptr)
{
    assert(buffer  != nullptr);
    assert(fileptr != nullptr);

    for (size_t i = 0; i < n; ++i)
    {
        if (buffer[i] == '\0')
        {

            #if defined OS_WINDOWS_

            ++i;

            #endif

            putc('\n', fileptr);
        }
        else
            putc(buffer[i], fileptr);
    }
}

static size_t getFileSize(FILE *fileptr)
{
    fseek(fileptr, 0L, SEEK_END);

    size_t size = ftell(fileptr);

    rewind(fileptr);

    return size;
}
