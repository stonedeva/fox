#include "lib/vector.h"

vector_t* vector_init(const size_t capacity) {
    vector_t* vector = (vector_t*)malloc(sizeof(vector_t));
    vector->data = malloc(capacity * sizeof(char*));
    vector->capacity = capacity;
    vector->size = 0;

    return vector;
}

void vector_delete(vector_t* vector) {
    vector->capacity = 0;
    vector->size = 0;
    vector->data = NULL;
    free(vector->data);
}

void vector_resize(vector_t* vector, const size_t new_capacity) {
    vector->data = (char**)realloc(vector->data, new_capacity * sizeof(char*));
}

bool vector_is_full(vector_t* vector) {
    return vector->size + 1 > vector->capacity;
}

void vector_push(vector_t* vector, const char* data) {
    if (vector_is_full(vector))
	vector_resize(vector, vector->capacity * 2);

    vector->data[vector->size] = strdup(data);
    vector->size++;
}

void vector_pop(vector_t* vector) {
    if (vector->size == 0)
	return;

    vector->data[vector->size] = NULL;
    vector->size--;
}

char* vector_get(vector_t* vector, const size_t index) {
    if (index > vector->size)
	return NULL;

    return vector->data[index];
}

void vector_set(vector_t* vector, const char* data, const size_t index) {
    if (vector->size > index)
	return;

    vector->data[index] = data;
}
