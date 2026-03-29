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
#include "rle.h"


// make new file extension: X.prev => X.tsur
char *make_tsur(char *filepath) {
    if (filepath == NULL) return NULL;  
    char *newpath = malloc(strlen(filepath) + 6);
    if (newpath == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    strcpy(newpath, filepath);
    char *dot_position = strrchr(newpath, '.');
    if (dot_position != NULL) {
        *dot_position = '\0';
    }
    strcat(newpath, ".tsur");
    return newpath;
}

// return to prev file extension: x.tsur => x.prev
char *kill_tsur(char *filepath) {
    if (filepath == NULL) return NULL;
    FILE *fp = fopen(filepath, "rb");
    if (fp == NULL) return NULL;
    struct Header header;
    if (fread(&header, sizeof(struct Header), 1, fp) != 1) {
        fclose(fp);
        return NULL;
    }
    fclose(fp);

    if (header.magic != MAGIC_HEADER) {
        return NULL;
    }
    header.filename[MAX_FILENAME - 1] = '\0';

    char *dot_position = strrchr(filepath, '.'); 
    char *oldext = strchr(header.filename, '.');

    size_t base_len = (dot_position != NULL) ? (size_t)(dot_position - filepath) : strlen(filepath);
    size_t ext_len = (oldext != NULL) ? strlen(oldext) : 0;

    char *newpath = malloc(base_len + ext_len + 1);
    if (newpath == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    memcpy(newpath, filepath, base_len);
    if (oldext != NULL) {
        strcpy(newpath + base_len, oldext); 
    } else {
        newpath[base_len] = '\0';
    }
    return newpath;
}

// check path string validity (no filesystem access)
// ret: ironmouse = 1, didy = 0
int tsuridity(char *filepath) {
    if (filepath == NULL || filepath[0] == '\0') {
        fprintf(stderr, "Path is NULL or empty.\n");
        return 0; // fein didy
    }
    if (strlen(filepath) >= PATH_MAX) {
        fprintf(stderr, "Path exceeds maximum length.\n");
        return 0; // fein didy
    }
    return 1; // wholesome ironmouse 
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