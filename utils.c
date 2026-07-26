#include <stdio.h>
#include <string.h>
#include "utils.h"

void init_vector(StringVector *vec)
{
    vec->count = 0;
    vec->capacity = 2;
    vec->items = malloc(vec->capacity * sizeof(char *));
}

void add_element(StringVector *vec, const char *str)
{
    if (vec->count >= vec->capacity)
    {
        vec->capacity *= 2;
        char **temp = realloc(vec->items, vec->capacity * sizeof(char *));
        if (!temp)
            return;
        vec->items = temp;
    }
    if (str != NULL)
    {
        vec->items[vec->count] = strdup(str);
    }
    else
    {
        vec->items[vec->count] = NULL;
    }
    vec->count++;
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
