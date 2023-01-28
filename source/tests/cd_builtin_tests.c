#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "include/cd_builtin_tests.h"
#include "include/get_filename_ext_tests.h"

void test_cd_builtin() {
    char cwd[1024];
    char *prev_dir = getcwd(cwd, sizeof(cwd)); // store the current working directory

    // Test 1: Test with path set to HOME
    cd_builtin("~");
    if (strcmp(getcwd(cwd, sizeof(cwd)), getenv("HOME")) == 0) {
        printf("Test 1 Passed\n");
    } else {
        printf("Test 1 Failed\n");
    }

    // Test 2: Test with path set to parent directory
    cd_builtin("..");
    if (strcmp(getcwd(cwd, sizeof(cwd)), prev_dir) == 0) {
        printf("Test 2 Passed\n");
    } else {
        printf("Test 2 Failed\n");
    }

    // Test 3: Test with path set to root directory
    cd_builtin("/");
    if (strcmp(getcwd(cwd, sizeof(cwd)), "/") == 0) {
        printf("Test 3 Passed\n");
    } else {
        printf("Test 3 Failed\n");
    }

    // Test 4: Test with path set to previous directory
    cd_builtin("-");
    if (strcmp(getcwd(cwd, sizeof(cwd)), getenv("HOME")) == 0) {
        printf("Test 4 Passed\n");
    } else {
        printf("Test 4 Failed\n");
    }

    // Test 5: Test with path set to a non-existing directory
    cd_builtin("nonexistent_directory");
    if (strcmp(getcwd(cwd, sizeof(cwd)), getenv("HOME")) == 0) {
        printf("Test 5 Passed\n");
    } else {
        printf("Test 5 Failed\n");
    }
}

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
