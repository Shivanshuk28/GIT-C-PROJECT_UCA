#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <openssl/sha.h>
#include "../include/commit.h"
#include "../include/index.h"

#define LOG_FILE ".trackit/log"

// Function to generate a hash of the index file content (used as commit ID)
char *generate_commit_id() {
    FILE *index_file = fopen(".trackit/index", "rb");
    if (index_file == NULL) {
        perror("Error opening index file");
        return NULL;
    }

    // Calculate file size
    fseek(index_file, 0, SEEK_END);
    long file_size = ftell(index_file);
    fseek(index_file, 0, SEEK_SET);

    // Read the entire file content
    unsigned char *file_content = (unsigned char *)malloc(file_size);
    fread(file_content, 1, file_size, index_file);
    fclose(index_file);

    // Compute SHA-1 hash of the entire file content
    unsigned char hash[SHA_DIGEST_LENGTH];
    SHA1(file_content, file_size, hash);

    // Convert the hash to a hex string
    char *commit_id = (char *)malloc(2 * SHA_DIGEST_LENGTH + 1); // 40 hex chars + null terminator
    for (int i = 0; i < SHA_DIGEST_LENGTH; i++) {
        sprintf(&commit_id[i * 2], "%02x", hash[i]);
    }
    commit_id[2 * SHA_DIGEST_LENGTH] = '\0'; // Null terminator

    free(file_content); // Clean up

    return commit_id;
}

// Function to get the current timestamp
char *get_timestamp() {
    time_t now = time(NULL);
    char *timestamp = (char *)malloc(20);
    strftime(timestamp, 20, "%Y-%m-%d %H:%M:%S", localtime(&now));
    return timestamp;
}

void git_commit(const char *message) {
    // Generate commit ID based on the index file hash
    char *commit_id = generate_commit_id();
    if (commit_id == NULL) {
        return;
    }

    // Check if a commit with the same ID already exists
    FILE *log_file = fopen(LOG_FILE, "r");
    if (log_file == NULL) {
        perror("Error opening log file");
        free(commit_id);
        return;
    }

    char line[256];
    int commit_exists = 0;
    while (fgets(line, sizeof(line), log_file)) {
        // Check if the line contains the commit ID
        if (strncmp(line, "Commit ID: ", 11) == 0 && strstr(line, commit_id) != NULL) {
            commit_exists = 1;
            break;
        }
    }
    fclose(log_file);

    if (commit_exists) {
        printf("No changes detected. Commit with ID %s already exists.\n", commit_id);
        free(commit_id);
        return;
    }

    // Open log file for appending
    log_file = fopen(LOG_FILE, "a");
    if (log_file == NULL) {
        perror("Error opening log file");
        free(commit_id);
        return;
    }

    char *timestamp = get_timestamp();

    // Write commit information to the log file
    fprintf(log_file, "Commit ID: %s\n", commit_id);
    fprintf(log_file, "Timestamp: %s\n", timestamp);
    fprintf(log_file, "Message: %s\n", message);

    // Save file paths and their corresponding blob hashes
    fprintf(log_file, "Files:\n");
    for (int i = 0; i < HASH_MAP_SIZE; i++) {
        FileEntry *entry = hash_map[i];
        if (entry != NULL) {
            BlobNode *blob = entry->blobs;
            while (blob != NULL) {
                fprintf(log_file, "- %s: %s\n", entry->file_path, blob->hash);
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
