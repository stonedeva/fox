#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdlib.h>
#include <stdbool.h>

// Define the hash table entry structure
typedef struct entry {
    char *key;
    void *value;
    struct Entry *next;
} entry_t;

// Define the hash table structure
typedef struct {
    size_t size;
    entry_t **buckets;
} hashtable_t;

// Function prototypes
hashtable_t *hashtable_create(size_t size);
void hashtable_destroy(hashtable_t *table);
bool hashtable_insert(hashtable_t *table, const char *key, void *value);
void *hashtable_lookup(const hashtable_t *table, const char *key);
bool hashtable_remove(hashtable_t *table, const char *key);
entry_t* hashtable_get_entry(hashtable_t *table, const char *key);

#endif // HASHTABLE_H

