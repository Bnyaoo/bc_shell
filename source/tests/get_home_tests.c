#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/get_home_tests.h"

void test_get_home() {
    char filename1[] = "~/test.txt";
    char filename2[] = "test.txt";
    char filename3[] = "~/test/file.txt";
    char filename4[] = "/test/file.txt";

    // Test 1: Test with valid filename starting with '~/'
    char *result1 = get_home(filename1);
    if (strcmp(result1, getenv("HOME")) == 0) {
        printf("Test 1 Passed\n");
    } else {
        printf("Test 1 Failed\n");
    }

    // Test 2: Test with valid filename without starting with '~/'
    char *result2 = get_home(filename2);
    if (strcmp(result2, filename2) == 0) {
        printf("Test 2 Passed\n");
    } else {
        printf("Test 2 Failed\n");
    }

    // Test 3: Test with valid filename starting with '~/' and '/'
    char *result3 = get_home(filename3);
    if (strcmp(result3, getenv("HOME")) == 0) {
        printf("Test 3 Passed\n");
    } else {
        printf("Test 3 Failed\n");
    }

    // Test 4: Test with valid filename starting with '/'
    char *result4 = get_home(filename4);
    if (strcmp(result4, filename4) == 0) {
        printf("Test 4 Passed\n");
    } else {
        printf("Test 4 Failed\n");
    }
}

char* get_home(char *filename) {
    for (int i = 0, j; filename[i] != '\0'; ++i) {

        // enter the loop if the character is not an alphabet
        // and not the null character
        while ((filename[i] == '~' || filename[i] == '/') &&
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