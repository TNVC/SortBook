#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
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


char **sortByChapters(char *strings[], size_t n, char newChapterSep)
{
    assert(strings != nullptr);

    for (size_t i = 0; i < n; ++i)
        assert(strings[i] != nullptr);

    int chapterCount = -1;

    char **chapterStart = strings;
    size_t chapterLen   = 0;

    for (size_t i = 0; i < n; ++i, ++chapterLen)
        if (strings[i][0] == newChapterSep)
        {
            ++chapterCount;

            sortStringArray(chapterStart, chapterLen - 1, chapterCount == 3 ? reverseStringComparator : stringComparator);

            chapterStart = strings + i + 1;

            chapterLen = 0;
        }

    return strings;
}

char **sortStringArray(char *strings[], size_t n, int (*funcptr)(const void *first, const void *second))
{
    assert(strings != nullptr);

    for (size_t i = 0; i < n; ++i)
        assert(strings[i] != nullptr);

    qsort(strings, n, sizeof(char *), funcptr);

    return strings;
}

int stringComparator(const void *first, const void *second)
{
    assert(first  != nullptr);
    assert(second != nullptr);

    const char *fstring = *((const char **) first);
    const char *sstring = *((const char **) second);

    size_t i = 0, j = 0;

    while (fstring[i] && sstring[j])
    {
        while (!isLetter(fstring[i]) && fstring[i] != '\0')
            ++i;

        while (!isLetter(sstring[j]) && sstring[j] != '\0')
            ++j;

        if (fstring[i] == '\0' || sstring[j] == '\0')
            continue;

        int compRes = charComparator(fstring[i], sstring[j]);

        if (compRes == 0)
        {
            ++i, ++j;

            continue;
        }

        return compRes;
    }

    return charComparator(fstring[i], sstring[j]);
}

int reverseStringComparator(const void *first, const void *second)
{
    assert(first  != nullptr);
    assert(second != nullptr);

    const char *fstring = *((const char **) first);
    const char *sstring = *((const char **) second);

    size_t i = strlen(fstring) - 1, j = strlen(sstring) - 1;

    while (i > 0 && j > 0)
    {
        while (!isLetter(fstring[i]) && i > 0)
            --i;

        while (!isLetter(sstring[j]) && j > 0)
            --j;

        if (i == 0 || j == 0)
            continue;

        int compRes = charComparator(fstring[i], sstring[j]);

        if (compRes == 0)
        {
            --i, --j;

            continue;
        }

        return compRes;
    }

    return charComparator(fstring[i], sstring[j]);
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

static int isLetter(char ch)
{
    for (int i = 0; alphabet[i]; ++i)
        if (ch == alphabet[i])
            return 1;

    return 0;
}
