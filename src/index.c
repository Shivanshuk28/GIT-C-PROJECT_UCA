#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/index.h"
#include "../include/blob.h"

#define HASH_MAP_SIZE 1024


// Global hash map to store the index entries
FileEntry *hash_map[HASH_MAP_SIZE];


// Function to initialize the index (optional, for clearing or setup purposes)
void init_index() {
    for (int i = 0; i < HASH_MAP_SIZE; i++) {
        hash_map[i] = NULL;
    }
}


// Simple hash function (from your implementation)
unsigned int hash_function(const char *str) {
    unsigned int hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }
    return hash % HASH_MAP_SIZE;
}


// Function to retrieve an entry from the hash map
FileEntry *get_entry(const char *file_path) {
    unsigned int index = hash_function(file_path);
    FileEntry *entry = hash_map[index];

    // Basic check to ensure the entry matches the requested file_path
    if (entry != NULL && strcmp(entry->file_path, file_path) == 0) {
        return entry;
    }

    return NULL; // Entry not found
}

void add_version(const char *file_path, const char *new_hash) {
    unsigned int index = hash_function(file_path);
    FileEntry *entry = hash_map[index];

    // If entry does not exist, create a new FileEntry
    if (entry == NULL) {
        entry = (FileEntry *)malloc(sizeof(FileEntry));
        entry->file_path = strdup(file_path);
        entry->blobs = NULL;
        hash_map[index] = entry;
    }

    // Create a new BlobNode for the new hash
    BlobNode *new_node = (BlobNode *)malloc(sizeof(BlobNode));
    strcpy(new_node->hash, new_hash);
    new_node->next = entry->blobs;
    entry->blobs = new_node;
}

void git_add(const char *file_path) {
    // Create a new blob from the file
    Blob *blob = create_blob(file_path);
    if (blob == NULL) {
        fprintf(stderr, "Error creating blob for %s\n", file_path);
        return;
    }

    // Convert the SHA-1 hash to a hex string
    char hash_str[41];
    for (int i = 0; i < 20; i++) {
        sprintf(&hash_str[i * 2], "%02x", blob->hash[i]);
    }

    // Add or update the file entry with a new version
    add_version(file_path, hash_str);

    // Write the blob to the objects directory
    write_blob(blob);

    printf("Added %s to index with hash %s\n", file_path, hash_str);

    // Clean up
    free(blob->content);
    free(blob);
}

// Helper function to check if a file path and hash are already in the index
int is_entry_present(const char *file_path, const char *hash) {
    FILE *file = fopen(".trackit/index", "r");
    if (file == NULL) {
        return 0; // If file doesn't exist, entry can't be present
    }

    char existing_file_path[256];
    char existing_hash[41];

    while (fscanf(file, "%s %s", existing_file_path, existing_hash) == 2) {
        if (strcmp(existing_file_path, file_path) == 0 && strcmp(existing_hash, hash) == 0) {
            fclose(file);
            return 1; // Entry found
        }
    }

    fclose(file);
    return 0; // Entry not found
}

void save_index() {
    FILE *file = fopen(".trackit/index", "a");
    if (file == NULL) {
        perror("Error opening .trackit/index for writing");
        return;
    }

    for (int i = 0; i < HASH_MAP_SIZE; i++) {
        FileEntry *entry = hash_map[i];
        while (entry != NULL) {
            BlobNode *blob = entry->blobs;
            while (blob != NULL) {
                // Only write the entry if it's not already present in the indexs
                if (!is_entry_present(entry->file_path, blob->hash)) {
                    fprintf(file, "%s %s\n", entry->file_path, blob->hash);
                }
                
                blob = blob->next;
            }
            entry = NULL; // Since we don’t have next pointer, only one entry per bucket.
        }
    }

    fclose(file);
}




// Function to load the index from a file
void load_index() {
    FILE *file = fopen(".trackit/index", "rb");
    if (file == NULL) {
        // perror("Error opening index file for reading");
        return;
    }

    char file_path[256];
    char hash[41];
    while (fread(file_path, sizeof(file_path), 1, file) == 1) {
        if (strlen(file_path) == 0) continue; // Skip empty entries
        unsigned int index = hash_function(file_path);
        FileEntry *entry = hash_map[index];

        // If entry does not exist, create a new FileEntry
        if (entry == NULL) {
            entry = (FileEntry *)malloc(sizeof(FileEntry));
            entry->file_path = strdup(file_path);
            entry->blobs = NULL;
            hash_map[index] = entry;
        }

        // Read blobs for this file
        while (fread(hash, 41, 1, file) == 1) {
            BlobNode *new_node = (BlobNode *)malloc(sizeof(BlobNode));
            strcpy(new_node->hash, hash);
            new_node->next = entry->blobs;
            entry->blobs = new_node;
        }
    }

    fclose(file);
}


void free_index() {
    for (int i = 0; i < HASH_MAP_SIZE; i++) {
        if (hash_map[i] != NULL) {
            // Free the linked list of blobs
            BlobNode *current = hash_map[i]->blobs;
            while (current != NULL) {
                BlobNode *temp = current;
                current = current->next;
                free(temp);
            }
            // Free the file path
            free(hash_map[i]->file_path);
            // Free the FileEntry itself
            free(hash_map[i]);
            hash_map[i] = NULL; // Set the hash_map entry to NULL
        }
    }
}



