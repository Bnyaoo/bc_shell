#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

#include "../include/find_command_path.h"

char* find_command_path(const char* command) {

    char* path_env = getenv("PATH"); // gets the PATH environment variable
    char* path = strdup(path_env); // creates a copy of the PATH variable
    char* current_path = strtok(path, ":"); // tokenizes the PATH variable by ':'
    char* command_path = NULL;

    while (current_path != NULL) {
        // builds the full path of the command by concatenating the current path and the command
        char* full_path = (char*) malloc(strlen(current_path) + strlen(command) + 2);
        strcpy(full_path, current_path);
        strcat(full_path, "/");
        strcat(full_path, command);

        // checks if the full path exists
        if (access(full_path, F_OK) == 0) {
            command_path = full_path;
            break;
        }
        free(full_path);
        current_path = strtok(NULL, ":");
    }

    free(path);
    return command_path;
}