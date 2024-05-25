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
} Vector;

#define VECTOR_INIT(vec, initial_capacity, type) vector_init(&(vec), initial_capacity, sizeof(type))

#define VECTOR_PUSH_BACK(vec, value) \
    do { \
        typeof(value) __temp = (value); \
        vector_push_back(&(vec), &__temp); \
    } while (0)

void vector_init(Vector *vec, size_t initial_capacity, size_t element_size);
void vector_push_back(Vector *vec, const void *value);
void *vector_at(Vector *vec, size_t index);
void vector_free(Vector *vec);

#endif