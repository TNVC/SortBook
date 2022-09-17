#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "heapfunctions.h"
#include "line.h"
#include "fiofunctions.h"
#include "copyfunctions.h"
#include "sortfunctions.h"
#include "newmergesort.h"
#include "logging.h"

const static char *DEFAULT_TARGET_FILE_NAME = "sortbook.txt";

int main(const int argc, const char *argv[])
{
    setlocale(LC_ALL, "");

    if (argc < 2)
    {
        printf("Incorrect use!!\n%s [source file name] [target file name]\n", argv[0]);

        return 0;
    }

    if (argc < 3 || argc > 3)
        printf("Incorrect use!!\n%s [source file name] [target file name]\n", argv[0]);

    if (argc < 3)
        printf("Set target file to default: \"%s\"\n", DEFAULT_TARGET_FILE_NAME);

    Strings strings = {};

    constructor(&strings);

    strings.size = readFile(&strings.originBuffer, argv[1]);

    if (strings.size == (size_t) FAIL_TO_OPEN)
    {
        printf("Fail to open \"%s\"!!\n", argv[1]);

        return 0;
    }

    if (strings.size == (size_t) OUT_OF_MEM)
    {
        printf("Line %d: Out of memory exception!!\n", __LINE__);

        return 0;
    }

    FILE *targetFile = nullptr;

    if (argc >= 3)
        targetFile = fopen(argv[2]                 , "w");
    else
        targetFile = fopen(DEFAULT_TARGET_FILE_NAME, "w");

    if (targetFile == nullptr)
    {
        printf("Fail to open \"%s\"!!\n", argc >= 3 ? argv[2] : DEFAULT_TARGET_FILE_NAME);

        destructor(&strings);

        return 0;
    }

    strings.sequence = getStringArray(strings.originBuffer, strings.size, &strings.stringCount);

    qsort          (strings.sequence, strings.stringCount, sizeof(String), stringComparator);

    writeAllLines  (strings.sequence, strings.stringCount, targetFile);

    newMergeSort   (strings.sequence, strings.stringCount, sizeof(String), reverseStringComparator);

    writeAllLines  (strings.sequence, strings.stringCount, targetFile);

    writeBuffer(strings.originBuffer, strings.size, targetFile);

    fclose(targetFile);

    destructor(&strings);

    return 0;
}
