//
// Created by Benny Chao on 2023-01-23.
//

#ifndef SRC_BC_SHELL_EXECUTE_COMMAND_REDIRECTION_TESTS_H
#define SRC_BC_SHELL_EXECUTE_COMMAND_REDIRECTION_TESTS_H

int execute_command_redirection(const char* command, char* const args[], const char* output_file, const char* error_file, int output_append, int error_append);

void test_execute_command_redirection();

#endif //SRC_BC_SHELL_EXECUTE_COMMAND_REDIRECTION_TESTS_H
