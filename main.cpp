#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "fiofunctions.h"
#include "copyfunctions.h"

static void showArray(char **arr, size_t n);

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
    }

    char **lines = nullptr;

    size_t size = 0;

    setlocale(LC_ALL, "");

    lines = readAllLines(&size, fileptr);

    if (lines == nullptr)
    {
        printf("Out of memory exception!!\n");

        return 0;
    }

    //showArray(lines + size - 150, 150);

    cleanStringArray(lines, size);

    fclose(fileptr);

    return 0;
}


static void showArray(char **arr, size_t n)
{
    for (size_t i = 0; i < n; ++i)
        printf("%s", arr[i]);
}
