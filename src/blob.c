#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <openssl/sha.h>
#include "../include/blob.h"

Blob *create_blob(const char *file_path) {
    FILE *file = fopen(file_path, "rb");
    if (file == NULL) {
        perror("Error opening file");
        return NULL;
    }
    // Get file size
    fseek(file, 0, SEEK_END);
    size_t size = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Read file content
    char *content = (char *)malloc(size);
    fread(content, 1, size, file);
    fclose(file);

    // Create blob object
    Blob *blob = (Blob *)malloc(sizeof(Blob));
    blob->content = content;
    blob->size = size;

    // Compute SHA-1 hash
    SHA1((unsigned char *)content, size, blob->hash);

    return blob;
}

void write_blob(Blob *blob) {
    // Convert the hash to a hex string for the filename
    char hash_str[41];
    for (int i = 0; i < 20; i++) {
        sprintf(&hash_str[i * 2], "%02x", blob->hash[i]);
    }   

    // Create the directory based on the first two characters of the hash
    char dir_path[256];
    sprintf(dir_path, ".trackit/objects/%.2s", hash_str);  // First two characters of the hash

    // Create the directory if it doesn't exist
    struct stat st = {0};
    if (stat(dir_path, &st) == -1) {
        mkdir(dir_path, 0700);  // Create directory with read/write/execute permissions for the owner
    }

    // Create the file path using the remaining 38 characters of the hash
    char file_path[512];
    snprintf(file_path, sizeof(file_path), "%s/%.38s", dir_path, hash_str + 2);

    // Write the blob content to the file
    FILE *file = fopen(file_path, "wb");
    if (file == NULL) {
        perror("Error creating blob file");
        return;
    }
    fwrite(blob->content, 1, blob->size, file);
    fclose(file);
}
