#include <stdio.h>
#include <limits.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include "io.h"



// check path string validity (no filesystem access)
// ret: ironmouse = 1, didy = 0
int tsuridity(char *filepath) {
    if (filepath == NULL || filepath[0] == '\0') {
        fprintf(stderr, "Path is NULL or empty.\n");
        return 0;
    }
    if (strlen(filepath) >= PATH_MAX) {
        fprintf(stderr, "Path exceeds maximum length.\n");
        return 0;
    }
    return 1;
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