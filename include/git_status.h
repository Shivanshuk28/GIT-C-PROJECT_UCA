// git_status.h
#ifndef GIT_STATUS_H
#define GIT_STATUS_H

// Function declarations
void git_status();

// Helper function to calculate the hash of a file
char *calculate_file_hash(const char *file_path);

#endif // GIT_STATUS_H
