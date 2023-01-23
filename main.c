#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/file.h>

char* find_command_path(const char* command);
int execute_command(const char* path, char* const args[]);
void cd_builtin(const char* path);
int execute_command_redirection(const char* command, char* const args[], const char* output_file, const char* error_file, int output_append, int error_append);
char* get_filename_ext(const char *filename);
char* remove_special_characters(char *filename);

int main() {
    char input[100];
    int status = 2;
    char* error_file = NULL;
    int error_append = 0;


    while (1) {
        char* output_file = NULL;
        // flush stdin for new user input in case last command was newline
        fflush(stdin);
        // prompt and take command
        printf("Benny@bc_shell $ ");
        scanf("%[^\n]%*c", input);
        // new line
        if (strcmp(input, "\0") == 0) {
            strcpy(input, "");
            continue;
        }
        // tokenize user input to retrieve command and potential arguments
        char* token = strtok(input, " ");
        // exit command
        if (strcmp(token, "exit") == 0) {
            break;
        }
        // builtin cd commands
        else if (strcmp(token, "cd") == 0) {
            token = strtok(NULL, " ");
            cd_builtin(token);
        }
        // ./a.out command
        else if (strcmp(token, "./a.out") == 0) {
            char* a_out = "./a.out";
            execute_command(a_out, NULL);
            printf("\n");
            continue;
        } else { // command execution
            char* args[100];
            int i = 0;
            while(token != NULL) {
                // truncate
                if (strcmp(token, ">") == 0) {
                    token = strtok(NULL, " ");
                    output_file = token;
                    status = 0;
                    break;
                }
                // append
                else if (strcmp(token, ">>") == 0) {
                    token = strtok(NULL, " ");
                    output_file = token;
                    status = 1;
                    break;
                } else if (strcmp(token, "2>") == 0) {
                    error_file = &token[i + 1];
                    i++;
                    status = 0;
                    break;
                } else if (strcmp(token, "2>>") == 0) {
                    error_file = &token[i + 1];
                    error_append = 1;
                    i++;
                    status = 1;
                    break;
                }
                args[i++] = token;
                token = strtok(NULL, " ");
            }
            args[i] = NULL;
            args[0][strcspn(args[0], "\n")] = 0;
            char* path = find_command_path(args[0]);
            // error if path cannot be found for command
            if(path == NULL) {
                printf("command: %s not found\n", input);
                continue;
            }
            // standard command execution
            if (status == 2) {
                execute_command(path, args);
            } else { // command execution with I/O redirection
                execute_command_redirection(path, args, output_file, error_file, status, error_append);
            }
        }
    }
    return 0;
}

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

//int execute_command_redirection(const char* command, char* const args[], const char* output_file, int append) {
//    int output_fd;
//    pid_t pid;
//    int status;
//    // Open output file for writing
//    if (output_file != NULL) {
//        if(append){
//            output_fd = open(output_file, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
//        }
//        else{
//            output_fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
//        }
//        if (output_fd == -1) {
//            printf("Error: Unable to open output file %s\n", output_file);
//            return -1;
//        }
//    }
//    pid = fork();
//    if (pid == 0) {
//        if (output_file != NULL) {
//            dup2(output_fd, 1); // redirect stdout to the output file
//        }
//        execv(command, args);
//        _exit(1);
//    }
//    else if (pid > 0) {
//        wait(&status);
//    }
//    else {
//        printf("Error: Unable to fork a new process\n");
//        return -1;
//    }
//    if (output_file != NULL) {
//        close(output_fd);
//    }
//    return 0;
//}

int execute_command_redirection(const char* command, char* const args[], const char* output_file, const char* error_file, int output_append, int error_append) {
    int output_fd, error_fd;
    pid_t pid;
    int status;
    char* raw_file_name;
    for (int i = sizeof(output_file); i > 0; i--) {
        if (strchr(&output_file[i], '/') == 0){
            cd_builtin("~");
            raw_file_name = remove_special_characters((char*)output_file);
            output_file = raw_file_name;
            break;
        }
    }
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

char* get_filename_ext(const char *filename) {
    char *dot = strrchr(filename, '.');
    if(!dot || dot == filename) return "";
    return dot + 1;
}

char* remove_special_characters(char *filename) {
    for (int i = 0, j; filename[i] != '\0'; ++i) {

        // enter the loop if the character is not an alphabet
        // and not the null character
        while (!(filename[i] >= 'a' && filename[i] <= 'z') && !(filename[i] >= 'A' && filename[i] <= 'Z' || filename[i] == '.') &&
               filename[i] != '\0') {
            for (j = i; filename[j] != '\0'; ++j) {

                // if jth element of line is not an alphabet,
                // assign the value of (j+1)th element to the jth element
                filename[j] = filename[j + 1];
            }
            filename[j] = '\0';
        }
    }

    return filename;
}


