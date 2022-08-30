#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "line.h"
#include "fiofunctions.h"
#include "copyfunctions.h"
#include "sortfunctions.h"
#include "newmergesort.h"

const static char *DEFAULT_TARGET_FILE_NAME = "sortbook.txt";

int compInt(const void *f, const void *s)
{
    return *((const int*)f) - *((const int*)s);
}

int main(int argc, char *argv[])
{
    const int s = 12;

    int arr[] = {11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};

    newMergeSort(arr, s, sizeof(int), compInt);

    for (int i = 0; i < s; ++i)
        printf("%d ", arr[i]);
    putchar('\n');

    return 0;

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

    FILE *fileptr = nullptr;

    fileptr = fopen(argv[1], "rb");

    if (fileptr == nullptr)
    {
        printf("Fail to open \"%s\"!!\n", argv[1]);

        return 0;
    }

    char *originLines = nullptr;

    size_t size = 0;

    size = readAllLines(&originLines, fileptr);

    fclose(fileptr);

    if (size == (size_t) OUT_OF_MEM)
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

        free(originLines);

        return 0;
    }

    size_t lines = 0;

    String *strings = getStringArray(originLines, size, &lines);

    size_t nn = 10;

    sortStringArray(strings, nn, stringComparator);

    writeAllLines(strings, nn, targetFile);

    sortStringArray(strings, nn, reverseStringComparator);

    writeAllLines(strings, nn, targetFile);

    writeBuffer(originLines, size, targetFile);

    fclose(targetFile);

    free(originLines);
    free(strings);

    return 0;
}
