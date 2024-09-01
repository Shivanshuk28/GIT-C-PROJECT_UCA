#include <stdio.h>
#include <string.h>
#include "include/init.h"
#include "include/index.h"

int main() {
    char command[50];
    char file_path[100];

    while (1) {
        printf("Enter command: ");
        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = 0; // Remove newline character

        // Handle 'trackit' command for initializing the repository
        if (strcmp(command, "trackit") == 0) {
            git_init();
        }
        // Handle 'git add <filename>' command
        else if (strncmp(command, "git add", 7) == 0) {
            sscanf(command, "git add %s", file_path); // Extract the filename
            git_add(file_path); // Call the function to add the file
        }
        // Handle 'exit' command to quit the program
        else if (strcmp(command, "exit") == 0) {
            printf("Exiting...\n");
            break;
        }
        // Handle unknown commands
        else {
            printf("Unknown command\n");
        }
    }

    return 0;
}
