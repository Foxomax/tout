#include <stdio.h>
#include <string.h>
#include "utils.h"

int init_vector(StringVector *vec)
{
    vec->count = 0;
    vec->capacity = 2;
    char **temp = malloc(vec->capacity * sizeof(char *));
    if (!temp)
        return -1;

    vec->items = temp;

    return 0;
}

int add_element(StringVector *vec, const char *str)
{
    if (vec->count >= vec->capacity)
    {
        vec->capacity *= 2;
        char **temp = realloc(vec->items, vec->capacity * sizeof(char *));
        if (!temp)
            return -1;
        vec->items = temp;
    }
    if (str != NULL)
    {
        vec->items[vec->count] = strdup(str);
        if (!vec->items[vec->count])
            return -1;
    }
    else
    {
        vec->items[vec->count] = NULL;
    }
    vec->count++;
    return 0;
}

void free_vector(StringVector *vec)
{
    for (size_t i = 0; i < vec->count; i++)
    {
        if (vec->items[i] != NULL)
        {
            free(vec->items[i]);
        }
    }
    free(vec->items);
}

long parsing_to_long(const char *str)
{
    char *finalptr;
    long number = strtol(str, &finalptr, 0);
    if (str == finalptr || *finalptr != '\0')
    {
        return -1;
    }
    return number;
}
