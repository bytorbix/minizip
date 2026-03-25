#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>


static inline char* extract_filename(const char *path);
FILE* feinpen(const char *filepath, const char *mode);
void feinlose(FILE *fp);
int tsuridity(char *filepath);
int is_tsur(char *filepath);