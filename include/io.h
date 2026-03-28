#include <stdio.h>
#include <limits.h>
#ifndef PATH_MAX
#define PATH_MAX 4096
#endif
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>


static inline char* extract_filename(const char *path) {
    char *filename = strrchr(path, '/');
    if (filename == NULL) return (char *)path;
    return filename + 1;
}
FILE* feinpen(const char *filepath, const char *mode);
void feinlose(FILE *fp);
int tsuridity(char *filepath);
int is_tsur(char *filepath);
char *make_tsur(char *filepath);
char *kill_tsur(char *filepath);
