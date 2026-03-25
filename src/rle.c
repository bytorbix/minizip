#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "rle.h"

#define maxChar 100

void *rle_encode(uint8_t *in, uint32_t in_len, uint8_t **out, size_t *out_len)
{
    char *buf = malloc(in_len * 2 + 1);
    if (!buf) return NULL;

    char charCount[maxChar];
    size_t i = 0, j = 0;
    int cLen = 0;

    for (i = 0; i < in_len; i++)
    {
        buf[j++] = in[i];

        cLen = 1;
        while (i + 1 < in_len && in[i] == in[i+1]) {
            cLen++;
            i++;
        }
        sprintf(charCount, "%d", cLen);

        for (int k = 0; charCount[k]; k++) {
            buf[j++] = charCount[k];
        }
    }
    buf[j] = '\0';
    *out_len = j;
    *out = (uint8_t *)buf;
    return buf;
}

// decrypt/decode file
// DeTsur
static void tsur_out(uint8_t *in, size_t in_len, uint8_t **out, size_t out_len) {
    uint8_t *buffer = malloc(out_len);
    if (buffer == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    size_t i = 0, j = 0;
    while (i + 1 < in_len) {
        uint8_t val = in[i];
        uint8_t count = in[i+1];
        for (uint8_t k = 0; k < count; k++) {
            if (j < out_len) {
                buffer[j++] = val;
            }
        }
        i += 2;
    }
    *out = buffer;
}
