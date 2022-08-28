#include <assert.h>
#include <string.h>
#include <ctype.h>
#include "sortfunctions.h"


/// Compare two Kirilic or zero chars
/// @param [in] first First char
/// @param [in] second Second char
/// @return 0 if first == second, negative value if first < second, positive value if first > second
static int charComparator(char first, char second);


String *sortStringArray(String strings[], size_t n, int (*funcptr)(const void *first, const void *second))
{
    assert(strings != nullptr);
    assert(funcptr != nullptr);

    for (size_t i = 0; i < n; ++i)
        assert(strings[i].value != nullptr);

    qsort(strings, n, sizeof(String), funcptr);

    return strings;
}

int stringComparator(const void *first, const void *second)
{
    assert(first  != nullptr);
    assert(second != nullptr);

    const String *fstring = (const String *) first;
    const String *sstring = (const String *) second;

    size_t i = 0, j = 0;

    while (fstring->value[i] && sstring->value[j])
    {
        while (!(isalpha(fstring->value[i]) || fstring->value[i] == 'ÿ') && fstring->value[i] != '\0')
            ++i;

        while (!(isalpha(sstring->value[j]) || sstring->value[j] == 'ÿ') && sstring->value[j] != '\0')
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
        while (!(isalpha(fstring->value[i]) || fstring->value[i] == 'ÿ') && i > 0)
            --i;

        while (!(isalpha(sstring->value[j]) || sstring->value[j] == 'ÿ') && j > 0)
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

    char *nearFirst  = strchr("ÅÆ", first);
    char *nearSecond = strchr("ÅÆ", second);

    if ((first == '¨' || second  == '¨') &&  nearFirst == nullptr && nearSecond == nullptr)
    {
        first  = (first  == '¨') ? 'Å' : first;
        second = (second == '¨') ? 'Å' : second;
    }
    else if (first  == '¨' && nearSecond)
        return (second == 'Å') ?  1 : -1;
    else if (second == '¨' && nearFirst)
        return (first == 'Å')  ? -1 :  1;

    return first - second;
}
