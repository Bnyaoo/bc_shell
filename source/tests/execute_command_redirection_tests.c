#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/file.h>
#include <ctype.h>

#include "include/execute_command_redirection_tests.h"

void test_execute_command_redirection() {
    char* args[] = {"ls", "-al", NULL};
    char* output_file = "test_output.txt";
    char* error_file = "test_error.txt";
    int status;

    // Test 1: Test with valid command, output file and error file
    status = execute_command_redirection("/bin/ls", args, output_file, error_file, 0, 0);
    if (status == 0) {
        printf("Test 1 Passed\n");
    } else {
        printf("Test 1 Failed\n");
    }

    // Test 2: Test with invalid command
    status = execute_command_redirection("/bin/invalid_command", args, output_file, error_file, 0, 0);
    if (status == -1) {
        printf("Test 2 Passed\n");
    } else {
        printf("Test 2 Failed\n");
    }

    // Test 3: Test with valid command and output append
    status = execute_command_redirection("/bin/ls", args, output_file, NULL, 1, 0);
    if (status == 0) {
        printf("Test 3 Passed\n");
    } else {
        printf("Test 3 Failed\n");
    }

    // Test 4: Test with valid command and error append
    status = execute_command_redirection("/bin/ls", args, NULL, error_file, 0, 1);
    if (status == 0) {
        printf("Test 4 Passed\n");
    } else {
        printf("Test 4 Failed\n");
    }
}

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
