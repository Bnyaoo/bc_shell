//
// Created by Benny Chao on 2023-01-23.
//

#ifndef BC_SHELL_EXECUTE_COMMAND_REDIRECTION_H
#define BC_SHELL_EXECUTE_COMMAND_REDIRECTION_H

int execute_command_redirection(const char* command, char* const args[], const char* output_file, const char* error_file, int output_append, int error_append);

#endif //BC_SHELL_EXECUTE_COMMAND_REDIRECTION_H
