#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/file.h>
#include <ctype.h>

#include "../include/execute_command_redirection.h"

int execute_command_redirection(const char* command, char* const args[], const char* output_file, const char* error_file, int output_append, int error_append) {
    int output_fd, error_fd;
    pid_t pid;
    int status;
    // Open output file for writing
    if (output_file != NULL) {
        if(output_append){
            output_fd = open(output_file, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
        }
        else{
            output_fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
        }
        if (output_fd == -1) {
            printf("Error: Unable to open output file %s\n", output_file);
            return -1;
        }
    }

    if(error_file != NULL){
        if(error_append){
            error_fd = open(error_file, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
        }
        else{
            error_fd = open(error_file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
        }
        if (error_fd == -1) {
            printf("Error: Unable to open error file %s\n", error_file);
            return -1;
        }
    }
    pid = fork();
    if (pid == 0) {
        if (output_file != NULL) {
            dup2(output_fd, 1); // redirect stdout to the output file
        }
        if(error_file != NULL){
            dup2(error_fd, 2); // redirect stderr to the error file
        }
        execv(command, args);
        _exit(1);
    }
    else if (pid > 0) {
        wait(&status);
    }
    else {
        printf("Error: Unable to fork a new process\n");
        return -1;
    }
    if (output_file != NULL) {
        close(output_fd);
    }
    return 0;
}
