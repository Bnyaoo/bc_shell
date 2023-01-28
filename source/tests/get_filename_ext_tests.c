#include <stdio.h>
#include <string.h>

#include "include/get_filename_ext_tests.h"

void test_get_filename_ext() {
    char* filename1 = "test.txt";
    char* filename2 = "test";
    char* filename3 = "test.file.txt";

    // Test 1: Test with valid filename with extension
    char* ext1 = get_filename_ext(filename1);
    if (strcmp(ext1, "txt") == 0) {
        printf("Test 1 Passed\n");
    } else {
        printf("Test 1 Failed\n");
    }

    // Test 2: Test with valid filename without extension
    char* ext2 = get_filename_ext(filename2);
    if (strcmp(ext2, "") == 0) {
        printf("Test 2 Passed\n");
    } else {
        printf("Test 2 Failed\n");
    }

    // Test 3: Test with valid filename with multiple extensions
    char* ext3 = get_filename_ext(filename3);
    if (strcmp(ext3, "txt") == 0) {
        printf("Test 3 Passed\n");
    } else {
        printf("Test 3 Failed\n");
    }
}

char* get_filename_ext(const char *filename) {
    char *dot = strrchr(filename, '.');
    if(!dot || dot == filename) return "";
    return dot + 1;
}
