#ifndef _VECTOR_H_
#define _VECTOR_H_
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
    void** data;
    size_t size;
    size_t capacity;
    size_t pointer;
} vector_t;

vector_t* vector_init(const size_t capacity);
void vector_delete(vector_t* vector);
void vector_push(vector_t* vector, const void* data);
void vector_pop(vector_t* vector);
char* vector_get(vector_t* vector, const size_t index);
void vector_set(vector_t* vector, const void* data, const size_t index);
void vector_resize(vector_t* vector, const size_t new_capacity);
bool vector_is_full(vector_t* vector);

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* _VECTOR_H_ */
