#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>
#include "../include/init.h"

void create_directory(const char *path) {
    if (mkdir(path, 0755) == -1) {
        if (errno != EEXIST) {
            perror("Error creating directory");
            exit(EXIT_FAILURE);
        }
    }
}


void git_init() {
    // Create the main .git directory
    create_directory(".trackit");
    // Create subdirectories within .git032
    create_directory(".trackit/objects");
    create_directory(".trackit/refs");
    create_directory(".trackit/refs/heads");

    // Create the HEAD file pointing to the master branch
    FILE *head = fopen(".trackit/HEAD", "w");
    if (head == NULL) {
        perror("Error creating HEAD file");
        exit(EXIT_FAILURE);
        //or could have written exit(1);
    }
    fprintf(head, "ref: refs/heads/master\n");
    fclose(head);

    // Create an empty config file
    FILE *config = fopen(".trackit/config", "w");
    if (config == NULL) {
        perror("Error creating config file");
        exit(EXIT_FAILURE);
    }
    fclose(config);

    printf("Initialized empty Git repository in .git/\n");
}
