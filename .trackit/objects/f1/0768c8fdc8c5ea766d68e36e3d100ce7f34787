#include <stdio.h>
#include <string.h>
#include<sys/stat.h>
#include "include/init.h"
#include "include/index.h"
#include "include/git_status.h"

int main() {
    char command[50];
    char file_path[100];
    //if .trackit not present then dont load_index() else load_index()

    // load_index();lllllddcxcsdcsdsbhbhdsdssdds

    while (1) {
        printf("Enter command: ");
        // 
        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = 0; // Remove newline characters

        // Handle 'trackit' command for initializing the repository
        if (strcmp(command, "trackit") == 0) {
            git_init();
        }
        // Handle 'git add <filename>' command
        else if (strncmp(command, "git add", 7) == 0) {
            load_index();
            sscanf(command, "git add %s", file_path); // 
            git_add(file_path); 
            save_index();
        }
        // Handle 'git status' command
        else if (strcmp(command, "git status") == 0) {
            git_status();
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
    free_index();

    return 0;
}
