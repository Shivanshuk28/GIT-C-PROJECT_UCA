#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "../include/index.h"
#include "../include/blob.h"

// Global pointer to the start of the index linked list
IndexEntry *index_head = NULL;

// Function to load the index linked list from the .trackit/index file
void load_index() {
    FILE *file = fopen(".trackit/index", "rb");
    if (!file) {
        // If the file doesn't exist, there's nothing to load
        return;
    }

    IndexEntry *prev = NULL;
    while (!feof(file)) {
        // Allocate a new entry
        IndexEntry *new_entry = (IndexEntry *)malloc(sizeof(IndexEntry));

        // Read the file path length and file path
        size_t path_len;
        fread(&path_len, sizeof(size_t), 1, file);
        new_entry->file_path = (char *)malloc(path_len);
        fread(new_entry->file_path, sizeof(char), path_len, file);

        // Read the hash
        fread(new_entry->hash, sizeof(char), 41, file);

        // Insert into the linked list
        new_entry->next = NULL;
        if (prev == NULL) {
            index_head = new_entry;
        } else {
            prev->next = new_entry;
        }
        prev = new_entry;
    }

    fclose(file);
}

// Function to save the index linked list to the .trackit/index file
void save_index() {
    FILE *file = fopen(".trackit/index", "wb");
    if (!file) {
        perror("Error opening index file for writing");
        return;
    }

    IndexEntry *current = index_head;
    while (current != NULL) {
        // Write the file path length and file path
        size_t path_len = strlen(current->file_path) + 1; // Include null terminator
        fwrite(&path_len, sizeof(size_t), 1, file);
        fwrite(current->file_path, sizeof(char), path_len, file);

        // Write the hash
        fwrite(current->hash, sizeof(char), 41, file);

        // Move to the next entry
        current = current->next;
    }

    fclose(file);
}

// Function to add a file to the index
void git_add(const char *file_path) {
    // Create a blob from the file
    Blob *blob = create_blob(file_path);
    if (blob == NULL) {
        fprintf(stderr, "Error creating blob for %s\n", file_path);
        return;
    }

    // Add the file to the index linked list
    IndexEntry *new_entry = (IndexEntry *)malloc(sizeof(IndexEntry));
    new_entry->file_path = strdup(file_path);

    // Convert the SHA-1 hash to a hex string
    for (int i = 0; i < 20; i++) {
        sprintf(&new_entry->hash[i * 2], "%02x", blob->hash[i]);
    }

    new_entry->next = index_head;
    index_head = new_entry;

    // Write the blob to the objects directory
    write_blob(blob);

    printf("Added %s to index with hash %s\n", file_path, new_entry->hash);

    // Save the updated index to the file
    save_index();

    // Clean up
    free(blob->content);
    free(blob);
}

// int main() {
//     // Load the existing index from the file
//     load_index();

//     // Add a file
//     git_add("cpp2.c");

//     return 0;
// }
