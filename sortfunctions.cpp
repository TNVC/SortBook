#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "sortfunctions.h"
#include "stringassert.h"
#include "newmergesort.h"


/// Compare two Kirilic or zero chars
/// @param [in] first First char
/// @param [in] second Second char
/// @return 0 if first == second, negative value if first < second, positive value if first > second
static int charComparator(char first, char second);


String *sortStringArray(String strings[], size_t n, int (*funcptr)(const void *first, const void *second))
{
    assert(strings != nullptr);
    assert(funcptr != nullptr);

    #ifndef NOT_DEBUG_MODE_

    for (size_t i = 0; i < n; ++i)
        stringAssert(strings[i].buff != nullptr, i);

    #endif

    newMergeSort(strings, n, sizeof(String), funcptr);

    return strings;
}

int stringComparator(const void *first, const void *second)
{
    assert(first  != nullptr);
    assert(second != nullptr);

    const String *fstring = (const String *) first;
    const String *sstring = (const String *) second;

    size_t i = 0, j = 0;

    while (fstring->buff[i] && sstring->buff[j])
    {
        while (!(isalpha(fstring->buff[i]) || fstring->buff[i] == 'ÿ') && fstring->buff[i] != '\0')///remake
            ++i;

        while (!(isalpha(sstring->buff[j]) || sstring->buff[j] == 'ÿ') && sstring->buff[j] != '\0')
            ++j;

        if (fstring->buff[i] == '\0' || sstring->buff[j] == '\0')
            continue;

        int compRes = charComparator(fstring->buff[i], sstring->buff[j]);

        if (compRes != 0)
            return compRes;

        ++i, ++j;
    }

    return charComparator(fstring->buff[i], sstring->buff[j]);
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
        while (!(isalpha(fstring->buff[i]) || fstring->buff[i] == 'ÿ') && i > 0)
            --i;

        while (!(isalpha(sstring->buff[j]) || sstring->buff[j] == 'ÿ') && j > 0)
            --j;

        if (i == 0 || j == 0)
            break;

        int compRes = charComparator(fstring->buff[i], sstring->buff[j]);

        if (compRes != 0)
            return compRes;

        --i, --j;
    }

    return charComparator(fstring->buff[i], sstring->buff[j]);
}

static int charComparator(char first, char second)
{
    first  = (char) toupper(first );
    second = (char) toupper(second);

    char *nearFirst  = (char *) strchr("ÅÆ", first);
    char *nearSecond = (char *) strchr("ÅÆ", second);

    if ((first == '¨' || second  == '¨') &&  nearFirst == nullptr && nearSecond == nullptr)
    {
        first  = (first  == '¨') ? 'Å' : first;
        second = (second == '¨') ? 'Å' : second;
    }
    else if (first  == '¨' && nearSecond)
        return (second == 'Å') ?  1 : -1;
    else if (second == '¨' && nearFirst)
        return (first  == 'Å') ? -1 :  1;

    return first - second;
}
