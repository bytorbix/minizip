#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>


// tsur wrapper 1
FILE* feinpen(const char *filepath, const char *mode) {
    if(filepath == NULL || !tsuridity(filepath)){
        return NULL;
    }
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
// ret: ironmouse = 1, didy = 0
int tsuridity(char *filepath){
    struct stat st;
    if (stat(filepath, &st) == 0) {
        printf("Path exists. ");
        if (S_ISDIR(st.st_mode)) {
            printf("directory.\n");
        } else if (S_ISREG(st.st_mode)) {
            printf("regular file.\n");
        }
        return 1; // returns wholesome ironmouse  
    } else {
        fprintf(stderr, "Path invalid or inaccessible. Errno: %d\n", errno);
        return 0; // returns evil didy
    }
}

// check if in base dir
// ret: if fein = true, if bal = false 
int is_tsur(char *filepath){
    if(!strchr(filepath, '/')){
        return 1;
    }
    return 0;
}