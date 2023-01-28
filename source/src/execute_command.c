#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <ctype.h>

#include "../include/execute_command.h"

int execute_command(const char* path, char* const args[]) {

    if (path == NULL) {
        return -1;
    }
    pid_t pid = fork();
    if (pid == 0) {
        // child process
        setpgid(0, 0); // Set process group ID to child 1's PID
        printf("Child (PID %d) in group %d\n", getpid(), getpgid(0));
        execv(path, args);
        printf("command: %s not found", path);
        exit(-1);
    } else if (pid > 0) {
        // parent process
        int status;
        waitpid(pid, &status, 0);
        printf("Parent (PID %d) in group %d\n", getpid(), getpgid(0));
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