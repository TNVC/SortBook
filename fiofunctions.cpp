#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/stat.h>
#include "line.h"
#include "fiofunctions.h"
#include "asserts.h"

/// Return file size
/// @param [in] filename Name of file
/// @return Size of file in byte
static size_t getFileSize(const char *filename);

/// Check that string has only space chars
/// @param [in] str Source string
/// @return 1 if string is space or 0 if string isn`t space
static int isSpaceString(const String *str);

size_t readFile(char **buffer, const char *filename)
{
    FUNC_START;

    pointerAssert(buffer,   nullptr);
    pointerAssert(filename, nullptr);

    FILE *fileptr = fopen(filename, "rb");

    LOG_LINE;

    if (fileptr == nullptr)
        RETURN((size_t) FAIL_TO_OPEN);

    LOG_LINE;

    size_t size = getFileSize(filename);

    *buffer = (char *) calloc(size + 1, sizeof(char));

    if (*buffer == nullptr)
    {
        fclose(fileptr);

        RETURN((size_t) OUT_OF_MEM);
    }

    LOG_LINE;

    if (fread(*buffer, sizeof(char), size, fileptr) != size)
    {
        fclose(fileptr);

        free(*buffer);

        RETURN((size_t) OUT_OF_MEM);
    }

    LOG_LINE;

    fclose(fileptr);

    RETURN(size);
}

void writeAllLines(String strings[], size_t size, FILE *fileptr)
{
    FUNC_START;

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

    RETURN_;
}

void writeBuffer(const char *buffer, size_t n, FILE *fileptr)
{
    FUNC_START;

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

    RETURN_;
}

static size_t getFileSize(const char *filename)
{
    FUNC_START;

    pointerAssert(filename, nullptr);

    LOG_LINE;

    struct stat temp = {};

    stat(filename, &temp);

    RETURN(temp.st_size);
}

static int isSpaceString(const String *str)
{
    FUNC_START;

    pointerAssert(str, nullptr);

    LOG_LINE;

    for (size_t i = 0; str->buff[i] != '\0'; ++i)
        if (!isspace(str->buff[i]))
            RETURN(0);

    RETURN(1);
}

