#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/index.h"
#include "../include/blob.h"

#define HASH_MAP_SIZE 1024

// Structure to store file metadata in the index
typedef struct FileEntry {
    char *file_path;            // Path to the file
    char hash[41];              // SHA-1 hash of the file content (40 characters + null terminator)
    struct FileEntry *next;     // Pointer to handle hash collisions (chaining)
} FileEntry;

// Global hash map to store the index entries
FileEntry *hash_map[HASH_MAP_SIZE] = {NULL};

// Function to calculate the index in the hash map from the SHA-1 hash
unsigned int hash_function(const char *hash) {
    unsigned int index = 0;
    for (int i = 0; hash[i] != '\0'; i++) {
        index = (index * 31 + hash[i]) % HASH_MAP_SIZE;
    }
    return index;
}

// Function to add a file to the hash map
void add_file_to_hash_map(const char *file_path, const char *hash) {
    unsigned int index = hash_function(hash);
    FileEntry *new_entry = (FileEntry *)malloc(sizeof(FileEntry));

    if (new_entry == NULL) {
        fprintf(stderr, "Error: Unable to allocate memory for new entry.\n");
        return;
    }

    new_entry->file_path = strdup(file_path);
    strcpy(new_entry->hash, hash);
    new_entry->next = hash_map[index];
    hash_map[index] = new_entry;

    printf("Added %s to index with hash %s\n", file_path, new_entry->hash);
}

// Function to write a blob and add its entry to the index
void git_add(const char *file_path) {
    // Create a blob from the file
    Blob *blob = create_blob(file_path);
    if (blob == NULL) {
        fprintf(stderr, "Error creating blob for %s\n", file_path);
        return;
    }

    // Convert the SHA-1 hash to a hex string
    char hash_hex[41];
    for (int i = 0; i < 20; i++) {
        sprintf(&hash_hex[i * 2], "%02x", blob->hash[i]);
    }
    hash_hex[40] = '\0';

    // Add the file to the hash map
    add_file_to_hash_map(file_path, hash_hex);

    // Write the blob to the objects directory
    write_blob(blob);

    // Clean up
    free(blob->content);
    free(blob);
}

// Function to initialize the index (optional, for clearing or setup purposes)
void init_index() {
    for (int i = 0; i < HASH_MAP_SIZE; i++) {
        hash_map[i] = NULL;
    }
}

// Function to free the allocated memory in the hash map
void free_index() {
    for (int i = 0; i < HASH_MAP_SIZE; i++) {
        FileEntry *entry = hash_map[i];
        while (entry != NULL) {
            FileEntry *temp = entry;
            entry = entry->next;
            free(temp->file_path);
            free(temp);
        }
        hash_map[i] = NULL;
    }
}
