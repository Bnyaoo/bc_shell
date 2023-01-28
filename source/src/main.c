#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "../include/cd_builtin.h"
#include "../include/execute_command.h"
#include "../include/get_special_chars.h"
#include "../include/get_home.h"
#include "../include/find_command_path.h"
#include "../include/execute_command_redirection.h"


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
        printf("Benny@source $ ");
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
                    char* home = get_special_chars(output_file);
                    if (strcmp(home, "~/") == 0) {
                        output_file = get_home(output_file);
                        chdir(getenv("HOME")); // go to the home directory
                    }
                    status = 0;
                    break;
                }
                    // append
                else if (strcmp(token, ">>") == 0) {
                    token = strtok(NULL, " ");
                    output_file = token;
                    char* home = get_special_chars(output_file);
                    if (strcmp(home, "~/") == 0) {
                        output_file = get_home(output_file);
                        chdir(getenv("HOME")); // go to the home directory
                    }
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

