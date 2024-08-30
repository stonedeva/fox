#include "lib/vector.h"

vector_t* vector_init(const size_t capacity) {
    vector_t* vector = (vector_t*)malloc(sizeof(vector_t));
    vector->data = malloc(capacity * sizeof(void*)); // Allocate memory for data
    vector->capacity = capacity;
    vector->size = 0;
    vector->pointer = 0;

    return vector;
}

void vector_delete(vector_t* vector) {
    // Free each item in the vector
    for (size_t i = 0; i < vector->size; i++) {
        free(vector->data[i]);
    }
    free(vector->data); // Free the data array itself

    vector->capacity = 0;
    vector->size = 0;
    vector->data = NULL;
}

void vector_resize(vector_t* vector, const size_t new_capacity) {
    vector->data = (void**)realloc(vector->data, new_capacity * sizeof(void*));
    vector->capacity = new_capacity;
}

bool vector_is_full(vector_t* vector) {
    return vector->size >= vector->capacity; // Check if the vector is full
}

void vector_push(vector_t* vector, const void* data) {
    if (vector_is_full(vector)) {
        vector_resize(vector, vector->capacity * 2); // Resize if full
    }

    vector->data[vector->size] = (void*)data; // Store data
    vector->size++;
}

void vector_push_array(vector_t* vector, const char data[], size_t data_size) {
    for (size_t i = 0; i < data_size; i++) {
	char* opcode = (char*)malloc(sizeof(char));
	if (opcode == NULL)
	    return;
	*opcode = data[i];
	vector_push(vector, opcode);
    }
}

void vector_pop(vector_t* vector) {
    if (vector->size == 0)
        return;

    vector->size--;
    free(vector->data[vector->size]); // Free the popped item
    vector->data[vector->size] = NULL; // Set the pointer to NULL
}

char* vector_get(vector_t* vector, const size_t index) {
    if (index >= vector->size)
        return NULL;

    return vector->data[index]; // Return the data at the index
}

void vector_set(vector_t* vector, const void* data, const size_t index) {
    if (index >= vector->size)
        return;

    vector->data[index] = (void*)data; // Set the data at the index
}

char* vector_extract_charray(vector_t* vector) {
    if (vector->size == 0)
	return NULL;

    char* data = (char*)malloc(vector->size * sizeof(char));
    if (data == NULL)
	return NULL;

    for (size_t i = 0; i < vector->size; i++) {
	data[i] = *((char*)vector->data[i]);
    }

    vector->size = 0;

    return data;
}


size_t vector_get_size(vector_t* vector) {
    return vector->size;
}
