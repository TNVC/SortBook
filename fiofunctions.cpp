#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include "fiofunctions.h"
#include "line.h"
#include "stringassert.h"

/// Check that string has only space chars
/// @param [in] str Source string
/// @return 1 if string is space or 0 if string isn`t space
static int isSpaceString(const String *str);

/// Return file size
/// @param [in] fileptr File
/// @return Size of file in byte
static size_t getFileSize(FILE *fileptr);

size_t readAllLines(char **buffer, FILE *fileptr)
{
    assert(buffer  != nullptr);
    assert(fileptr != nullptr);

    size_t size = getFileSize(fileptr);

    *buffer = (char *) calloc(size, sizeof(char));

    if (*buffer == nullptr)
        return OUT_OF_MEM;

    if (fread(*buffer, sizeof(char), size, fileptr) != size)
    {
        free(*buffer);

        return (size_t) OUT_OF_MEM;
    }

    return size;
}

void writeAllLines(String strings[], size_t size, FILE *fileptr)
{
    assert(strings != nullptr);
    assert(fileptr != nullptr);

    #ifndef NOT_DEBUG_MODE_

    for (size_t i = 0; i < size; ++i)
        stringAssert(strings[i].buff != nullptr, i);

    #endif

    for (size_t i = 0; i < size; ++i)
        if (!isSpaceString(&strings[i]))
            fprintf(fileptr, "%s\n", strings[i].buff);
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

static int isSpaceString(const String *str)
{
    for (size_t i = 0; str->buff[i] != '\0'; ++i)
        if (!isspace(str->buff[i]))
            return 0;
    return 1;
}

static size_t getFileSize(FILE *fileptr)
{
    fseek(fileptr, 0L, SEEK_END);

    size_t size = ftell(fileptr);

    rewind(fileptr);

    return size;
}
