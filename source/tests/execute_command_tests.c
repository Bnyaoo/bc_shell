#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <ctype.h>

#include "include/execute_command_tests.h"

void test_execute_command() {
    int status;
    char* args[] = {"ls", "-al", NULL};

    // Test 1: Test with a valid command
    status = execute_command("/bin/ls", args);
    if (status == 0) {
        printf("Test 1 Passed\n");
    } else {
        printf("Test 1 Failed\n");
    }

    // Test 2: Test with an invalid command
    status = execute_command("/bin/invalid_command", args);
    if (status == -1) {
        printf("Test 2 Passed\n");
    } else {
        printf("Test 2 Failed\n");
    }

    // Test 3: Test with a NULL path
    status = execute_command(NULL, args);
    if (status == -1) {
        printf("Test 3 Passed\n");
    } else {
        printf("Test 3 Failed\n");
    }
}

int execute_command(const char* path, char* const args[]) {

    if (path == NULL) {
        return -1;
    }
    pid_t pid = fork();
    if (pid == 0) {
        // child process
        execv(path, args);
        printf("command: %s not found", path);
        exit(-1);
    } else if (pid > 0) {
        // parent process
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status)) {
            int exit_status = WEXITSTATUS(status);
            return exit_status;
        } else {
            printf("Command terminated abnormally\n");
            return -1;
        }
    } else {
        // fork failed
        printf("Fork failed\n");
        return -1;
    }
}