#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "include/get_special_chars_tests.h"

void test_get_special_chars() {
    char input1[] = "test-string";
    char input2[] = "test_string";
    char input3[] = "test!string";
    char input4[] = "test string";
    char input5[] = "test.string";

    // Test 1: Test with valid input containing '-'
    char* result1 = get_special_chars(input1);
    if (strcmp(result1, "-") == 0) {
        printf("Test 1 Passed\n");
    } else {
        printf("Test 1 Failed\n");
    }

    // Test 2: Test with valid input containing '_'
    char* result2 = get_special_chars(input2);
    if (strcmp(result2, "_") == 0) {
        printf("Test 2 Passed\n");
    } else {
        printf("Test 2 Failed\n");
    }

    // Test 3: Test with valid input containing '!'
    char* result3 = get_special_chars(input3);
    if (strcmp(result3, "!") == 0) {
        printf("Test 3 Passed\n");
    } else {
        printf("Test 3 Failed\n");
    }

    // Test 4: Test with valid input containing no special characters
    char* result4 = get_special_chars(input4);
    if (strcmp(result4, "") == 0) {
        printf("Test 4 Passed\n");
    } else {
        printf("Test 4 Failed\n");
    }

    // Test 5: Test with valid input containing '.'
    char* result5 = get_special_chars(input5);
    if (strcmp(result5, "") == 0) {
        printf("Test 5 Passed\n");
    } else {
        printf("Test 5 Failed\n");
    }
}

char* get_special_chars(const char* str) {
    int len = strlen(str);
    char* special_chars = malloc(len + 1);
    int index = 0;
    for (int i = 0; i < len; i++) {
        if (!isalnum(str[i]) && str[i] != '.') {
            special_chars[index++] = str[i];
        }
    }
    special_chars[index] = '\0';
    return special_chars;
}
