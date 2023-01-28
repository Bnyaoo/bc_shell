#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

#include "../include/cd_builtin.h"
#include "../include/get_filename_ext.h"

void cd_builtin(const char* path) {
    char cwd[1024];
    char *prev_dir = getcwd(cwd, sizeof(cwd)); // store the current working directory

    if(path == NULL || strcmp(path, "~")  == 0) {
        chdir(getenv("HOME")); // go to the home directory
    }
    else if (strcmp(path, "..") == 0) {
        chdir(".."); // go to the parent directory
    }
    else if (strcmp(path, "/") == 0) {
        chdir("/"); // go to the root directory
    }
    else if(strcmp(path, "-") == 0) {
        chdir(prev_dir); // go to the previous directory
    }
    else {
        if (chdir(path) != 0) {
            char* extension = get_filename_ext(path);
            if (strcmp(extension, "") == 0) {
                printf("cd: No such file or directory: %s\n", path);
            } else {
                printf("cd: Not a directory: %s\n", path);
            }
        }
    }
}