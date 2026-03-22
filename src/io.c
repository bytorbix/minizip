#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>

// tsur wrapper 1
FILE* feinpen(const char *filepath, const char *mode) {
    FILE *fp = fopen(filepath, mode);
    if (fp == NULL) {
        perror("f-error: Could not open file");
        exit(EXIT_SUCCESS); 
    }
    return fp;
}

// tsur wrapper 2
void feinlose(FILE *fp) {
    if (fp == NULL) return;
    if (fclose(fp) == EOF) {
        perror("f-error: Could not close file");
    }
}

// check path validity
// ret: 0 = success, -1 = error
bool tsuridity(char *filepath){
    struct stat st;
    if (stat(path, &st) == 0) {
        printf("Path exists. ");
        if (S_ISDIR(st.st_mode)) {
            printf("directory.\n");
        } else if (S_ISREG(st.st_mode)) {
            printf("regular file.\n");
        }
        return 1; // exists
    } else {
        fprintf(stderr, "Path invalid or inaccessible. Errno: %d\n", errno);
        return 0; 
    }
}