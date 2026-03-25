#include <stdint.h>
#include <stdio.h>

#define MAGIC_HEADER (0x74737572)
#define INT_SIZE (4)

struct Header {
    uint32_t magic;
    uint32_t size;
};