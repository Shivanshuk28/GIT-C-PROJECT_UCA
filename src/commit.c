#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/commit.h"
#include "../include/index.h"

#define LOG_FILE ".trackit/log"

// Function to generate a unique commit ID (you can improve this as needed)
char *generate_commit_id() {
    time_t now = time(NULL);
    char *commit_id = (char *)malloc(11 * sizeof(char));
    snprintf(commit_id, 11, "%lx", now);  // Convert timestamp to hex
    return commit_id;
}
// Function to get the current timestamp
char *get_timestamp() {
    time_t now = time(NULL);
    char *timestamp = (char *)malloc(20);
    strftime(timestamp, 20, "%Y-%m-%d %H:%M:%S", localtime(&now));
    return timestamp;
}

// Helper function to check if the file was already committed with the same hash
int is_already_committed(const char *file_path, const char *hash) {
    FILE *log_file = fopen(LOG_FILE, "r");
    if (log_file == NULL) {
        return 0; // Log file doesn't exist yet, meaning no commits
    }

    char line[256];
    char committed_file[256];
    char committed_hash[41];

    // Look for the file path and its corresponding hash
    while (fgets(line, sizeof(line), log_file)) {
        // Parse the line to find file paths and hashes in the log
        if (sscanf(line, "- %255s: %40s", committed_file, committed_hash) == 2) {
            // Check if the file path and hash match
            if (strcmp(file_path, committed_file) == 0 && strcmp(hash, committed_hash) == 0) {
                fclose(log_file);
                return 1;  // File has already been committed with the same hash
            }
        }
    }

    fclose(log_file);
    return 0;
}
void git_commit(const char *message) {
    int changes_found = 0;

    // First, check if there are any changes in the tracked files
    for (int i = 0; i < HASH_MAP_SIZE; i++) {
        FileEntry *entry = hash_map[i];
        if (entry != NULL) {
            BlobNode *blob = entry->blobs;
            while (blob != NULL) {
                if (!is_already_committed(entry->file_path, blob->hash)) {
                    changes_found = 1;
                    break;  // We found changes, no need to check further
                }
                blob = blob->next;
            }
        }
        if (changes_found) break;
    }

    // If no changes are found, exit the function
    if (!changes_found) {
        printf("No changes found. Commit not created.\n");
        return;
    }

    // If changes are found, proceed to write commit info to the log file
    FILE *log_file = fopen(LOG_FILE, "a");
    if (log_file == NULL) {
        perror("Error opening log file");
        return;
    }

    char *commit_id = generate_commit_id();
    char *timestamp = get_timestamp();

    // Write basic commit info
    fprintf(log_file, "Commit ID: %s\n", commit_id);
    fprintf(log_file, "Timestamp: %s\n", timestamp);
    fprintf(log_file, "Message: %s\n", message);

    // Save file paths and their corresponding blob hashes (tracked files)
    fprintf(log_file, "Files:\n");
    for (int i = 0; i < HASH_MAP_SIZE; i++) {
        FileEntry *entry = hash_map[i];
        if (entry != NULL) {
            BlobNode *blob = entry->blobs;
            while (blob != NULL) {
                if (!is_already_committed(entry->file_path, blob->hash)) {
                    fprintf(log_file, "- %s: %s\n", entry->file_path, blob->hash);
                }
                blob = blob->next;
            }
        }
    }
    fprintf(log_file, "\n");

    printf("Commit created with ID %s at %s\n", commit_id, timestamp);

    free(commit_id);
    free(timestamp);
    fclose(log_file);
}