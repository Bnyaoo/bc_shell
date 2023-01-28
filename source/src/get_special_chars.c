#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../include/get_special_chars.h"

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
