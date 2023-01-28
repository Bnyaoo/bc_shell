cmake_minimum_required(VERSION 3.23)
project(src/bc_shell C)

set(CMAKE_C_STANDARD 17)

enable_testing(cd_builtin_tests.c execute_command_redirection_tests.c execute_command_tests.c find_command_path_tests.c
        get_filename_ext_tests.c get_home_tests.c get_special_chars_tests.c)
add_test(cd_builtin_tests.c execute_command_redirection_tests.c execute_command_tests.c find_command_path_tests.c
        get_filename_ext_tests.c get_home_tests.c get_special_chars_tests.c)

add_executable(bc_shell_test main.c cd_builtin_tests.c execute_command_redirection_tests.c execute_command_tests.c
        find_command_path_tests.c get_filename_ext_tests.c get_home_tests.c get_special_chars_tests.c include/cd_builtin_tests.h include/find_command_path.h include/execute_command_redirection_tests.h include/execute_command_tests.h include/get_filename_ext_tests.h include/get_home_tests.h include/get_special_chars_tests.h)