cmake_minimum_required(VERSION 3.23)
project(bc_shell C)

set(CMAKE_C_STANDARD 17)

add_executable(bc_shell main.c ../include/execute_command.h ../include/execute_command_redirection.h
        ../include/cd_builtin.h ../include/find_command_path.h ../include/get_filename_ext.h
        ../include/get_home.h ../include/get_special_chars.h cd_builtin.c execute_command.c
        execute_command_redirection.c find_command_path.c get_filename_ext.c get_home.c get_special_chars.c)
