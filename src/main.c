#include <stdio.h>
#include <string.h>
#include "init.h"
#include "index.h"

int main() {
    char command[50];
    char file_path[100];

    printf("Enter command: ");
    fgets(command, sizeof(command), stdin);
    command[strcspn(command, "\n")] = 0; // Remove newline character

    if (strcmp(command, "git init") == 0) {
        git_init();
    } else if (strncmp(command, "git add", 7) == 0) {
        sscanf(command, "git add %s", file_path);
        git_add(file_path);
    } else {
        printf("Unknown command\n");
    }

    return 0;
}
