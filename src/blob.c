#include <stdio.h>
#include <stdlib.h>
#include <openssl/sha.h>
#include "blob.h"

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

    // Create the file path in the .git/objects directory
    char path[256];
    sprintf(path, ".git/objects/%s", hash_str);

    // Write the blob content to the file
    FILE *file = fopen(path, "wb");
    if (file == NULL) {
        perror("Error creating blob file");
        return;
    }
    fwrite(blob->content, 1, blob->size, file);
    fclose(file);
}
