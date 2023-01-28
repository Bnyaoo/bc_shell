#include <string.h>

#include "../include/get_filename_ext.h"

char* get_filename_ext(const char *filename) {
    char *dot = strrchr(filename, '.');
    if(!dot || dot == filename) return "";
    return dot + 1;
}
