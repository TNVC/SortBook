#include <string.h>
#include <assert.h>
#include <ctype.h>
#include "copyfunctions.h"


/// Check string is empty or not (empty == only space chars)
/// @param [in] str Source string
/// @return 1 if string is empty and 0 if string isn`t empty
static int isEmptyString(const char *str);


void cleanStringArray(char *strings[], size_t n)
{
    for (size_t i = 0; i < n; ++i)
        free(strings[i]);

    free(strings);
}

char **copyStringArray(char *strings[], size_t n, size_t *new_size)
{
    assert(strings  != nullptr);
    assert(new_size != nullptr);

    for (size_t i = 0; i < n; ++i)
        assert(strings[i] != nullptr);

    char **copyStrings = nullptr;

    copyStrings = (char **) calloc(n, sizeof(char *));

    if (copyStrings == nullptr)
        return nullptr;

    *new_size = 0;

    for (size_t i = 0; i < n; ++i)
    {
        if (isEmptyString(strings[i]))
            continue;

        if (strstr(strings[i], "Глава") == strings[i])
        {
            copyStrings[(*new_size)++] = strdup("#\n");

            if (copyStrings[*new_size - 1] == nullptr)
            {
                cleanStringArray(copyStrings, *new_size);

                *new_size = 0;

                return nullptr;
            }

            continue;
        }

        copyStrings[(*new_size)++] = strdup(strings[i]);

        if (copyStrings[*new_size - 1] == nullptr)
        {
            cleanStringArray(copyStrings, *new_size);

            *new_size = 0;

            return nullptr;
        }
    }

    copyStrings = (char **) realloc(copyStrings, *new_size * sizeof(char *));

    if (copyStrings == nullptr)
        return nullptr;

    return copyStrings;
}

static int isEmptyString(const char *str)
{
    assert(str != nullptr);

    for (int i = 0; str[i]; ++i)
        if (!isspace(str[i]))
            return 0;

    return 1;
}
