#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10  // Size of the hash table

// Node structure for storing key-value pairs (linked list for collisions)
typedef struct Node {
    char *key;
    int value;
    struct Node *next;
} Node;

// Hash table structure (array of node pointers)
typedef struct HashTable {
    Node *buckets[TABLE_SIZE];  // Array of pointers to linked lists
} HashTable;

// Hash function (simple djb2 hash function)
unsigned int hash(char *key) {
    unsigned long hash = 5381;
    int c;
    while ((c = *key++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash % TABLE_SIZE;
}

// Create a new node
Node* create_node(char *key, int value) {
    Node *new_node = (Node*) malloc(sizeof(Node));
    new_node->key = strdup(key); // Create a copy of the key
    new_node->value = value;
    new_node->next = NULL;
    return new_node;
}

// Initialize a hash table
HashTable* create_table() {
    HashTable *table = (HashTable*) malloc(sizeof(HashTable));
    for (int i = 0; i < TABLE_SIZE; i++) {
        table->buckets[i] = NULL; // Initialize all buckets to NULL
    }
    return table;
}

// Insert a key-value pair into the hash table
void insert(HashTable *table, char *key, int value) {
    unsigned int index = hash(key);
    Node *new_node = create_node(key, value);
    
    // Insert at the head of the linked list (for simplicity)
    if (table->buckets[index] == NULL) {
        table->buckets[index] = new_node;
    } else {
        // Collision: prepend the new node to the linked list
        new_node->next = table->buckets[index];
        table->buckets[index] = new_node;
    }
}

// Search for a key in the hash table
int search(HashTable *table, char *key) {
    unsigned int index = hash(key);
    Node *current = table->buckets[index];

    // Traverse the linked list at the index
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            return current->value; // Key found
        }
        current = current->next;
    }
    return -1; // Key not found
}

// Remove a key from the hash table
void delete(HashTable *table, char *key) {
    unsigned int index = hash(key);
    Node *current = table->buckets[index];
    Node *prev = NULL;

    while (current != NULL && strcmp(current->key, key) != 0) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Key not found.\n");
        return; // Key not found
    }

    if (prev == NULL) {
        // Removing the head of the linked list
        table->buckets[index] = current->next;
    } else {
        prev->next = current->next;
    }

    free(current->key); // Free the memory allocated for the key
    free(current); // Free the node itself
}

// Display the hash table
void display_table(HashTable *table) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node *current = table->buckets[i];
        printf("Bucket %d: ", i);
        while (current != NULL) {
            printf("(%s, %d) -> ", current->key, current->value);
            current = current->next;
        }
        printf("NULL\n");
    }
}

    HashTable *table = create_table();

    insert(table, "apple", 5);
    insert(table, "banana", 3);
    insert(table, "grape", 7);
    insert(table, "orange", 9);
    insert(table, "lemon", 2);

    printf("Table after insertions:\n");
    display_table(table);

    printf("\nSearch for 'apple': %d\n", search(table, "apple"));

