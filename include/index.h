#ifndef INDEX_H
#define INDEX_H

typedef struct IndexEntry {
    char *file_path;     // Path of the file being tracked
    char hash[41];       // SHA-1 hash of the file's content
    struct IndexEntry *next;
} IndexEntry;

void git_add(const char *file_path);
void save_index();
void load_index();
#endif
