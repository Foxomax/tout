#include <stdlib.h>
#include <string.h>

typedef struct
{
    char **items;
    size_t count;
    size_t capacity;
} StringVector;

int init_vector(StringVector *vec);

int add_element(StringVector *vec, const char *str);

void free_vector(StringVector *vec);

long parsing_to_long(const char *str);
