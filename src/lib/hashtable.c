#include "lib/hashtable.h"
#include <string.h>
#include <stdio.h>

// Hash function (simple modulo-based hash function)
static size_t hash(const char *key, size_t size) {
    size_t hash = 0;
    while (*key) {
        hash = (hash << 5) + *key++;
    }
    return hash % size;
}

// Create a new hash table
hashtable_t *hashtable_create(size_t size) {
    hashtable_t *table = malloc(sizeof(hashtable_t));
    if (!table) return NULL;
    table->size = size;
    table->buckets = calloc(size, sizeof(entry_t *));
    if (!table->buckets) {
        free(table);
        return NULL;
    }
    return table;
}

// Destroy a hash table
void hashtable_destroy(hashtable_t *table) {
    if (!table) return;

    for (size_t i = 0; i < table->size; i++) {
        entry_t *entry = table->buckets[i];
        while (entry) {
            entry_t *prev = entry;
            entry = entry->next;
            free(prev->key);
            free(prev);
        }
    }
    free(table->buckets);
    free(table);
}

// Insert a key-value pair into the hash table
bool hashtable_insert(hashtable_t *table, const char *key, void *value) {
    if (!table || !key) return false;

    size_t index = hash(key, table->size);
    entry_t *entry = table->buckets[index];

    // Check if the key already exists
    while (entry) {
        if (strcmp(entry->key, key) == 0) {
            // Key already exists, update value
            entry->value = value;
            return true;
        }
        entry = entry->next;
    }

    // Create a new entry
    entry_t *new_entry = malloc(sizeof(entry_t));
    if (!new_entry) return false;
    new_entry->key = strdup(key);
    if (!new_entry->key) {
        free(new_entry);
        return false;
    }
    new_entry->value = value;
    new_entry->next = table->buckets[index];
    table->buckets[index] = new_entry;

    return true;
}

// Lookup a value by key
void *hashtable_lookup(const hashtable_t *table, const char *key) {
    if (!table || !key) return NULL;

    size_t index = hash(key, table->size);
    entry_t *entry = table->buckets[index];

    while (entry) {
        if (strcmp(entry->key, key) == 0) {
            return entry->value;
        }
        entry = entry->next;
    }

    return NULL;
}

// Remove a key-value pair from the hash table
bool hashtable_remove(hashtable_t *table, const char *key) {
    if (!table || !key) return false;

    size_t index = hash(key, table->size);
    entry_t *entry = table->buckets[index];
    entry_t *prev = NULL;

    while (entry) {
        if (strcmp(entry->key, key) == 0) {
            if (prev) {
                prev->next = entry->next;
            } else {
                table->buckets[index] = entry->next;
            }
            free(entry->key);
            free(entry);
            return true;
        }
        prev = entry;
        entry = entry->next;
    }

    return false;
}

entry_t* hashtable_get_entry(hashtable_t *table, const char *key) {
    size_t index = hash(key, table->size);
    entry_t* entry = table->buckets[index];
    while (entry) {
        if (strcmp(entry->key, key) == 0) {
            return entry;
        }
        entry = entry->next;
    }
    return NULL;
}

