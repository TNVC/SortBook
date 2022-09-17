#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "sortfunctions.h"
#include "newmergesort.h"
#include "asserts.h"

/// Compare two Cirillik or zero chars
/// @param [in] first First char
/// @param [in] second Second char
/// @return 0 if first == second, negative value if first < second, positive value if first > second
static inline int charComparator(char first, char second);

int stringComparator(const void *first, const void *second)
{
    pointerAssert(first,  nullptr);
    pointerAssert(second, nullptr);

    LOG_LINE;

    const String *fstring = (const String *) first;
    const String *sstring = (const String *) second;

    pointerAssert(fstring->buff, nullptr);
    pointerAssert(sstring->buff, nullptr);

    size_t i = 0, j = 0;

    while (fstring->buff[i] && sstring->buff[j])
    {
        while (!isalpha((unsigned char)fstring->buff[i]) && fstring->buff[i] != '\0')
            ++i;

        while (!isalpha((unsigned char)sstring->buff[j]) && sstring->buff[j] != '\0')
            ++j;

        if (fstring->buff[i] == '\0' || sstring->buff[j] == '\0')
            continue;

        LOG_LINE;

        int compRes = charComparator(fstring->buff[i], sstring->buff[j]);

        if (compRes != 0)
            return compRes;

        ++i, ++j;
    }

    return charComparator(fstring->buff[i], sstring->buff[j]);
}

int reverseStringComparator(const void *first, const void *second)
{
    pointerAssert(first,  nullptr);
    pointerAssert(second, nullptr);

    LOG_LINE;

    const String *fstring = (const String *) first;
    const String *sstring = (const String *) second;

    pointerAssert(fstring->buff, nullptr);
    pointerAssert(sstring->buff, nullptr);

    size_t i = fstring->size - 1,
           j = sstring->size - 1;

    while (i > 0 && j > 0)
    {
        while (!isalpha((unsigned char)fstring->buff[i]) && i > 0)
            --i;

        while (!isalpha((unsigned char)sstring->buff[j]) && j > 0)
            --j;

        if (i == 0 || j == 0)
            break;

        LOG_LINE;

        int compRes = charComparator(fstring->buff[i], sstring->buff[j]);

        if (compRes != 0)
            return compRes;

        --i, --j;
    }

    return charComparator(fstring->buff[i], sstring->buff[j]);
}

static inline int charComparator(char first, char second)
{
    first  = (char) toupper(first );
    second = (char) toupper(second);

    char *nearFirst  = (char *) strchr("ÅÆ", first );
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
