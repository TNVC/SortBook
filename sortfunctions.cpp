#include <assert.h>
#include <string.h>
#include <ctype.h>

#include <stdio.h>

#include "sortfunctions.h"

/// Compare two Kirilic or zero chars
/// @param [in] first First char
/// @param [in] second Second char
/// @return 0 if first == second, negative value if first < second, positive value if first > second
static int charComparator(char first, char second);

/// Check is char a letter
/// @param [in] ch Char for check
/// @return 1 if ch is letter and 0 if char isn`t a letter
static int isLetter(char ch);


static const char alphabet[] = "ÀÁÂÃÄÅ¨ÆÇÈÉÊËÌÍÎÏĞÑÒÓÔÕÖ×ØÙÚÛÜİŞßàáâãäå¸æçèéêëìíîïğñòóôõö÷øùúûüışÿ";


String *sortStringArray(String strings[], size_t n, int (*funcptr)(const void *first, const void *second))
{
    assert(strings != nullptr);
    assert(funcptr != nullptr);

    for (size_t i = 0; i < n; ++i)
        assert(strings[i].value != nullptr);

    qsort(strings, n, sizeof(char *), funcptr);

    return strings;
}

int stringComparator(const void *first, const void *second)
{
    assert(first  != nullptr);
    assert(second != nullptr);

    const String *fstring = (const String *) first;
    const String *sstring = (const String *) second;

    size_t i = 0, j = 0;

    printf("1 i:%zd,j:%zd, %p\n", i, j,sstring);

    while (fstring->value[i] && sstring->value[j])
    {
        while (!isLetter(fstring->value[i]) && fstring->value[i] != '\0')
            ++i;

        while (!isLetter(sstring->value[j]) && sstring->value[j] != '\0')
            ++j;

        if (fstring->value[i] == '\0' || sstring->value[j] == '\0')
            continue;

        int compRes = charComparator(fstring->value[i], sstring->value[j]);

        if (compRes == 0)
        {
            ++i, ++j;

            continue;
        }

        return compRes;
    }

    return charComparator(fstring->value[i], sstring->value[j]);
}

int reverseStringComparator(const void *first, const void *second)
{
    assert(first  != nullptr);
    assert(second != nullptr);

    const String *fstring = (const String *) first;
    const String *sstring = (const String *) second;

    size_t i = fstring->size - 1, j = sstring->size - 1;

    while (i > 0 && j > 0)
    {
        while (!isLetter(fstring->value[i]) && i > 0)
            --i;

        while (!isLetter(sstring->value[j]) && j > 0)
            --j;

        if (i == 0 || j == 0)
            continue;

        int compRes = charComparator(fstring->value[i], sstring->value[j]);

        if (compRes == 0)
        {
            --i, --j;

            continue;
        }

        return compRes;
    }

    return charComparator(fstring->value[i], sstring->value[j]);
}

static int charComparator(char first, char second)
{
    first  = (char) toupper(first );
    second = (char) toupper(second);

    int fNum = 0, sNum = 0;

    for (int i = 0; alphabet[i]; ++i)
    {
        if (first  == alphabet[i])
            fNum = i + 1;
        if (second == alphabet[i])
            sNum = i + 1;
    }

    return fNum - sNum;
}

static int isLetter(char ch)  // this is krivo!!!
{
    for (int i = 0; alphabet[i]; ++i)
        if (ch == alphabet[i])
            return 1;

    return 0;
}
