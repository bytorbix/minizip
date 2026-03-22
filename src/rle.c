#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

static void tsur_in(uint8_t *in, size_t in_len, uint8_t **out, size_t *out_len){

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
            if (j < out_len) { // Safety check using the actual integer value
                buffer[j++] = val;
            }
        }
        i += 2;
    }
    *out = buffer;
}