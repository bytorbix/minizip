#include <stdint.h>
#include <stdio.h>

#define MAGIC_HEADER (0x72757374)
#define INT_SIZE (4)
#define MAX_FILENAME (30)

struct Header {
    uint32_t magic;
    uint32_t size;
    char filename[MAX_FILENAME];
};


size_t rle_encode(uint8_t *in, uint32_t in_len, uint8_t **out);
int tsur_compress(char *sfilepath, char *dfilepath);
int tsur_decompress(char *sfilepath, char *dfilepath);