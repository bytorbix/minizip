#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>



static inline char* extract_filename(const char *path) 
{
    char *filename = strrchr(path, '/');
    if (filename == NULL) {
        return NULL;
    }
    return filename+1;
}

// check path validity
// ret: ironmouse = 1, didy = 0
int tsuridity(char *filepath) {
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
// ret: if fein = true, bal = false 
int is_tsur(char *filepath) {
    if (strchr(filepath, '/')) {
        return 0;
    }
    if (strchr(filepath, '\\')) {
        return 0;
    }
    return 1;
}