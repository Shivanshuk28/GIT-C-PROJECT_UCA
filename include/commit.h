#ifndef COMMIT_H
#define COMMIT_H

// Function prototypes
char *generate_commit_id();
char *get_timestamp();
void git_commit(const char *message);

#endif // COMMIT_H
