#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include "fiofunctions.h"
#include "copyfunctions.h"
#include "sortfunctions.h"


int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "");

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

    char **originLines = nullptr;

    size_t size = 0;

    originLines = readAllLines(&size, fileptr);

    fclose(fileptr);

    if (originLines == nullptr)
    {
        printf("Line %d: Out of memory exception!!\n", __LINE__);

        return 0;
    }

    char **copyLines = nullptr;

    size_t copySize = 0;

    copyLines = copyStringArray(originLines, size, &copySize);

    if (copyLines == nullptr)
    {
        printf("Line %d: Out of memory exception!!\n", __LINE__);

        return 0;
    }

    sortByChapters(copyLines, copySize, '#');

    FILE *targetFile = fopen("sortbook.txt", "w");

    if (targetFile == nullptr)
        return 0;

    writeAllLines(copyLines  , copySize, targetFile);
    writeAllLines(originLines, size    , targetFile);


    fclose(targetFile);

    cleanStringArray(originLines, size);
    cleanStringArray(copyLines  , copySize);

    return 0;
}
