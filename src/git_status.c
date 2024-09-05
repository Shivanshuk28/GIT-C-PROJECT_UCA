// git_status.c
#include "../include/git_status.h"
#include "../include/index.h"  // Assuming you have this for FileEntry and hash_map
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include "../include/blob.h"  // Assuming you have this for calculating file hashes

// Helper function to calculate the hash of a file
// This assumes you already have a function to create a blob and calculate its hash
char *calculate_file_hash(const char *file_path) {
    Blob *blob = create_blob(file_path);  // Create a blob from the file
    if (blob == NULL) {
        return NULL;  // Error creating blob
    }

    // Convert the SHA-1 hash to a hex string
    char *hash_str = (char *)malloc(41 * sizeof(char));  // 40 characters + 1 for '\0'
    for (int i = 0; i < 20; i++) {
        sprintf(&hash_str[i * 2], "%02x", blob->hash[i]);
    }

    // Clean up
    free(blob->content);
    free(blob);

    return hash_str;
}

// Function to display the status of files in the working directory
void git_status() {
    struct dirent *entry;
    DIR *dir = opendir(".");

    if (dir == NULL) {
        perror("Unable to open current directory");
        return;
    }

    printf("Git Status:\n");

    // Scan each file in the working directory
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG) {  // Only regular files
            char *file_name = entry->d_name;

            // Calculate the hash of the file
            char *file_hash = calculate_file_hash(file_name);

            // Check if the file is in the index
            FileEntry *entry_in_index = get_entry(file_name);

            if (entry_in_index != NULL) {
                // File is in the index, compare its current hash
                BlobNode *current_blob = entry_in_index->blobs;
                if (strcmp(current_blob->hash, file_hash) == 0) {
                    printf("%s is staged for commit.\n", file_name);
                } else {
                    printf("%s has been modified but not added.\n", file_name);
                }
            } else {
                // File is not in the index
                printf("\033[31m%s is untracked.\n", file_name);
            }

            free(file_hash);  // Clean up memory after calculating hash
        }
    }

    closedir(dir);
}
