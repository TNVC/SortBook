#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/stat.h>
#include "line.h"
#include "fiofunctions.h"
#include "asserts.h"

/// Check that string has only space chars
/// @param [in] str Source string
/// @return 1 if string is space or 0 if string isn`t space
static int isSpaceString(const String *str);

/// Return file size
/// @param [in] filename Name of file
/// @return Size of file in byte
static size_t getFileSize(const char *filename);

size_t readAllLines(char **buffer, const char *filename)
{
    pointerAssert(buffer,   nullptr);
    pointerAssert(filename, nullptr);

    FILE *fileptr = fopen(filename, "rb");

    LOG_LINE;

    if (fileptr == nullptr)
        return (size_t) FAIL_TO_OPEN;

    LOG_LINE;

    size_t size = getFileSize(filename);

    *buffer = (char *) calloc(size, sizeof(char));

    if (*buffer == nullptr)
    {
        fclose(fileptr);

        return (size_t) OUT_OF_MEM;
    }

    LOG_LINE;

    if (fread(*buffer, sizeof(char), size, fileptr) != size)
    {
        fclose(fileptr);

        free(*buffer);

        return (size_t) OUT_OF_MEM;
    }

    LOG_LINE;

    fclose(fileptr);

    return size;
}

void writeAllLines(String strings[], size_t size, FILE *fileptr)
{
    pointerAssert(strings, nullptr);
    pointerAssert(fileptr, nullptr);

    #ifndef NOT_DEBUG_MODE_

    for (size_t i = 0; i < size; ++i)
        pointerIndexAssert(strings[i].buff, nullptr, i);

    #endif

    LOG_LINE;

    for (size_t i = 0; i < size; ++i)
        if (!isSpaceString(&strings[i]))
            fprintf(fileptr, "%s\n", strings[i].buff);
}

void writeBuffer(const char *buffer, size_t n, FILE *fileptr)
{
    pointerAssert(buffer,  nullptr);
    pointerAssert(fileptr, nullptr);

    LOG_LINE;

    for (size_t i = 0; i < n; ++i)
    {
        LOG_LINE;

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
    pointerAssert(str, nullptr);

    LOG_LINE;

    for (size_t i = 0; str->buff[i] != '\0'; ++i)
        if (!isspace(str->buff[i]))
            return 0;

    return 1;
}

static size_t getFileSize(const char *filename)
{
    pointerAssert(filename, nullptr);

    LOG_LINE;

    struct stat temp = {};

    stat(filename, &temp);

    return temp.st_size;
}
