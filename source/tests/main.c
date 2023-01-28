#include "include/cd_builtin_tests.h"
#include "include/execute_command_tests.h"
#include "include/execute_command_redirection_tests.h"
#include "include/find_command_path.h"
#include "include/get_special_chars_tests.h"
#include "include/get_home_tests.h"
#include "include/get_filename_ext_tests.h"


int main() {
    test_get_special_chars();
    test_get_home();
    test_get_filename_ext();
    test_find_command_path();
    test_execute_command();
    test_execute_command_redirection();
    test_cd_builtin();
    return 0;
}
