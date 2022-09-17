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
static int charComparator(char first, char second);

/// Increase size_t while buff[*index] != alpha
/// @param [in] buff Char buffer
/// @param [in/out] index Index of char in buff
static void skipNotAlpha(const char *buff, size_t *index);

/// Decrease size_t while buff[*index] != alpha
/// @param [in] buff Char buffer
/// @param [in/out] index Index of char in buff
static void reverseSkipNotAlpha(const char *buff, size_t *index);

int stringComparator(const void *first, const void *second)
{
    FUNC_START;

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
        skipNotAlpha(fstring->buff, &i);

        skipNotAlpha(sstring->buff, &j);

        if (fstring->buff[i] == '\0' || sstring->buff[j] == '\0')
            continue;

        LOG_LINE;

        int compRes = charComparator(fstring->buff[i], sstring->buff[j]);

        if (compRes != 0)
            RETURN(compRes);

        ++i, ++j;
    }

    RETURN(charComparator(fstring->buff[i], sstring->buff[j]));
}

int reverseStringComparator(const void *first, const void *second)
{
    FUNC_START;

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
        reverseSkipNotAlpha(fstring->buff, &i);

        reverseSkipNotAlpha(sstring->buff, &j);

        if (i == 0 || j == 0)
            break;

        LOG_LINE;

        int compRes = charComparator(fstring->buff[i], sstring->buff[j]);

        if (compRes != 0)
            RETURN(compRes);

        --i, --j;
    }

    RETURN(charComparator(fstring->buff[i], sstring->buff[j]));
}

static int charComparator(char first, char second)
{
    FUNC_START;

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
        RETURN((second == 'Å') ?  1 : -1)/// It`s scary
    else if (second == '¨' && nearFirst)
        RETURN((first  == 'Å') ? -1 :  1)/// It`s scary

    RETURN(first - second);
}

static void skipNotAlpha(const char *buff, size_t *index)
{
    FUNC_START;

    while (!isalpha((unsigned char)buff[*index]) && buff[*index] != '\0')
            ++(*index);

    RETURN_;
}

static void reverseSkipNotAlpha(const char *buff, size_t *index)
{
    FUNC_START;

    while (!isalpha((unsigned char)buff[*index]) && *index > 0)
            --(*index);

    RETURN_;
}
