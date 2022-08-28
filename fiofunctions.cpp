#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "fiofunctions.h"
#include "line.h"


size_t readAllLines(char **buffer, size_t *lines, FILE *fileptr)
{
    assert(buffer  != nullptr);
    assert(fileptr != nullptr);
    assert(lines   != nullptr);

    fseek(fileptr, 0L, SEEK_END);

    size_t size = ftell(fileptr);

    rewind(fileptr);

    *buffer = (char *) calloc(size, sizeof(char));

    if (*buffer == nullptr)
        return (size_t) EOF;

    int ch = 0;

    *lines = 0;

    for (size_t i = 0; (ch = getc(fileptr)) != EOF; ++i)
    {
        if (ch == '\n')
        {
            ++(*lines);

            ch = '\0';
        }

        (*buffer)[i] = (char) ch;
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
        putc(buffer[i] == '\0' ? '\n' : buffer[i], fileptr);
}
