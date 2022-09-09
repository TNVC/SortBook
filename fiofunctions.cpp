#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/stat.h>
#include <assert.h>
#include "line.h"
#include "fiofunctions.h"
#include "stringassert.h"

/// Check that string has only space chars
/// @param [in] str Source string
/// @return 1 if string is space or 0 if string isn`t space
static int isSpaceString(const String *str);

/// Return file size
/// @param [in] fileptr File
/// @return Size of file in byte
static size_t getFileSize(const char *filename);

size_t readAllLines(char **buffer, const char *filename)
{
    assert(buffer   != nullptr);
    assert(filename != nullptr);

    FILE *fileptr = fopen(filename, "rb");

    if (fileptr == nullptr)
        return (size_t) FAIL_TO_OPEN;

    size_t size = getFileSize(filename);

    *buffer = (char *) calloc(size, sizeof(char));

    if (*buffer == nullptr)
    {
        fclose(fileptr);

        return (size_t) OUT_OF_MEM;
    }

    if (fread(*buffer, sizeof(char), size, fileptr) != size)
    {
        fclose(fileptr);

        free(*buffer);

        return (size_t) OUT_OF_MEM;
    }

    fclose(fileptr);

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
    assert(str != nullptr);

    for (size_t i = 0; str->buff[i] != '\0'; ++i)
        if (!isspace(str->buff[i]))
            return 0;

    return 1;
}

static size_t getFileSize(const char *filename)
{
    assert(filename != nullptr);

    struct stat temp = {};

    stat(filename, &temp);

    return temp.st_size;
}
