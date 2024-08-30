#ifndef BLOB_H
#define BLOB_H

typedef struct {
    unsigned char hash[20]; // SHA-1 hash
    char *content;
    size_t size;
} Blob;

Blob *create_blob(const char *file_path);
void write_blob(Blob *blob);

#endif
