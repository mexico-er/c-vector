#include "vector.h"

void vector_init(vector *vec, size_t initial_capacity, size_t element_size, 
                 void (*copy_element)(void *dest, const void *src),
                 void (*free_element)(void *element)) {
    vec->data = malloc(initial_capacity * element_size);
    if (vec->data == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    vec->size = 0;
    vec->capacity = initial_capacity;
    vec->element_size = element_size;
    vec->copy_element = copy_element;
    vec->free_element = free_element;
}

void vector_push_back(vector *vec, const void *value) {
    if (vec->size >= vec->capacity) {
        size_t new_capacity = (vec->capacity == 0) ? 1 : vec->capacity * 2;
        void *new_data = realloc(vec->data, new_capacity * vec->element_size);
        if (new_data == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
        vec->data = new_data;
        vec->capacity = new_capacity;
    }
    void *dest = (char *)vec->data + vec->size * vec->element_size;
    if (vec->copy_element) {
        vec->copy_element(dest, value);
    } else {
        memcpy(dest, value, vec->element_size);
    }
    vec->size++;
}

void *vector_at(vector *vec, size_t index) {
    if (index >= vec->size) {
        fprintf(stderr, "Index out of bounds\n");
        exit(EXIT_FAILURE);
    }
    return (char *)vec->data + index * vec->element_size;
}

void vector_free(vector *vec) {
    if (vec->free_element) {
        for (size_t i = 0; i < vec->size; i++) {
            vec->free_element((char *)vec->data + i * vec->element_size);
        }
    }
    free(vec->data);
    vec->data = NULL;
    vec->size = 0;
    vec->capacity = 0;
}
