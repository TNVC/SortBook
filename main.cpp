#include <stdio.h>
#include <stdlib.h>
#include "line.h"
#include "fiofunctions.h"
#include "copyfunctions.h"
#include "sortfunctions.h"


int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Incorrect use!!\n%s [file name]\n", argv[0]);

        return 0;
    }

    if (argc > 2)
        printf("Incorrect use!!\n%s [file name]\n", argv[0]);

    FILE *fileptr = nullptr;

    fileptr = fopen(argv[1], "r");

    if (fileptr == nullptr)
    {
        printf("Fail to open \"%s\"!!\n", argv[1]);

        return 0;
    }

    char *originLines = nullptr;

    size_t size = 0, lines = 0;

    size = readAllLines(&originLines, &lines, fileptr);

    fclose(fileptr);

    if (size == (size_t) EOF)
    {
        printf("Line %d: Out of memory exception!!\n", __LINE__);

        return 0;
    }

    String *strings = getStringArray(originLines, lines);

    sortStringArray(strings, lines, stringComparator);

    FILE *targetFile = fopen("sortbook.txt", "w");

    if (targetFile == nullptr)
        return 0;

    writeAllLines(strings, lines, targetFile);

    sortStringArray(strings, lines, reverseStringComparator);

    writeAllLines(strings, lines, targetFile);

    writeBuffer(originLines, size, targetFile);

    fclose(targetFile);

    free(originLines);
    free(strings);

    return 0;
}
