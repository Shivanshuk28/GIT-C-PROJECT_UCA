// index.h
#ifndef INDEX_H
#define INDEX_H

typedef struct BlobNode {
    char hash[41];
    struct BlobNode *next;
} BlobNode;

typedef struct {
    char *file_path;
    BlobNode *blobs; // Linked list of blobs for this file
} FileEntry;

extern FileEntry *hash_map[];

void init_index();
unsigned int hash_function(const char *str);
FileEntry *get_entry(const char *file_path);
void add_version(const char *file_path, const char *new_hash);
void git_add(const char *file_path);
int is_entry_present(const char *file_path, const char *hash);
void save_index();
void free_index();
void load_index();
#endif // INDEX_H
