#include <stdlib.h>

typedef struct
{
    char **items;
    size_t count;
    size_t capacity;
} StringVector;

void init_vector(StringVector *vec);

void add_element(StringVector *vec, const char *str);

void free_vector(StringVector *vec);