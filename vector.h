#ifndef VECTOR_H
#define VECTOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    void *data;
    size_t size;
    size_t capacity;
    size_t element_size;
    void (*copy_element)(void *dest, const void *src);
    void (*free_element)(void *element);
} vector;

#define VECTOR_INIT(vec, initial_capacity, type) \
    vector_init(&(vec), initial_capacity, sizeof(type), NULL, NULL)

#define VECTOR_INIT_CUSTOM(vec, initial_capacity, type, copy_func, free_func) \
    vector_init(&(vec), initial_capacity, sizeof(type), copy_func, free_func)

#define VECTOR_PUSH_BACK(vec, value) \
    do { \
        typeof(value) __temp = (value); \
        vector_push_back(&(vec), &__temp); \
    } while (0)

void vector_init(vector *vec, size_t initial_capacity, size_t element_size, 
                 void (*copy_element)(void *dest, const void *src),
                 void (*free_element)(void *element));
void vector_push_back(vector *vec, const void *value);
void *vector_at(vector *vec, size_t index);
void vector_free(vector *vec);

#endif
