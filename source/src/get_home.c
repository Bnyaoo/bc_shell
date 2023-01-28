#include "../include/get_home.h"

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