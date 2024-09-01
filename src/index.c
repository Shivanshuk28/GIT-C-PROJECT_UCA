#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/index.h"
#include "../include/blob.h"

// Global pointer to the start of the index linked list
IndexEntry *index_head = NULL;

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

    // Clean up
    free(blob->content);
    free(blob);
}
