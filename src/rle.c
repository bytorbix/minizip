#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "rle.h"
#include "io.h"
#define maxChar 100

size_t *rle_encode(uint8_t *in, uint32_t in_len, uint8_t **out)
{
    char *buf = malloc(in_len * 2 + 1);
    if (!buf) return -1;

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
    *out = (uint8_t *)buf;
    return j;
}

// decrypt/decode file
// DeTsur
static void tsur_out(uint8_t *in, size_t in_len, uint8_t **out, size_t *out_len) {
    uint8_t *buffer = malloc(*out_len);
    if (buffer == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    size_t i = 0, j = 0;
    while (i + 1 < in_len) {
        uint8_t val = in[i];
        uint8_t count = in[i+1];
        for (uint8_t k = 0; k < count; k++) {
            if (j < *out_len) {
                buffer[j++] = val;
            }
        }
        i += 2;
    }
    *out = buffer;
}

int tsur_compress(char *sfilepath, char *dfilepath) {
    FILE *sfp = fopen(sfilepath, "rb");
    if (sfp == NULL) {
        return -1;
    }
    FILE *dfp = fopen(dfilepath, "wb");
    if (dfp == NULL) {
        fclose(sfp);
        return -1;
    }

    char *filename = extract_filename(sfilepath);
    struct Header header;
    header.magic = MAGIC_HEADER;
    header.filename = filename;
    
    uint32_t in_len = 0;
    uint8_t *in = NULL;
    fseek(sfp, 0, SEEK_END);
    in_len = ftell(sfp); // length of the file to be compressed

    in = malloc(in_len);
    if (in == NULL) {
        fclose(sfp);
        fclose(dfp);
        return -1;
    }

    if (fread(in, 1, in_len, sfp) != in_len) {
        free(in);
        fclose(sfp);
        fclose(dfp);
        return -1;
    }
    fclose(sfp);

    uint8_t *out = NULL;
    size_t bytes_compressed = rle_encode(in, &in_len, &out);
    if (bytes_compressed == -1) {
        fclose(dfp);
        free(in);
        return -1;
    }

    if (fwrite(out, 1, bytes_compressed, dfp) != byte_compressed) {
        free(out);
        fclose(dfp);
        return -1;
    }
    return 1;

}


// decompress the file
// removes feinder, uses the tsur_out()™ method, so smart😻
// DeTsur 2
int tsur_decompress(char *sfilepath, char *dfilepath) {
    FILE *sfp = fopen(sfilepath, "rb");
    if (sfp == NULL) {
        return -1;
    }
    FILE *dfp = fopen(dfilepath, "wb");
    if (dfp == NULL) {
        fclose(sfp);
        return -1;
    }

    struct Header header;
    if (fread(&header, sizeof(struct Header), 1, sfp) != 1 || header.magic != MAGIC_HEADER) {
        fclose(sfp);
        fclose(dfp);
        return -1;
    }

    uint32_t in_len = 0;
    uint8_t *in = NULL;
    fseek(sfp, 0, SEEK_END);
    in_len = ftell(sfp) - sizeof(struct Header); // telling file length to decode
    fseek(sfp, sizeof(struct Header), SEEK_SET);

    in = malloc(in_len);
    if (in == NULL) {
        fclose(sfp);
        fclose(dfp);
        return -1;
    }

    if (fread(in, 1, in_len, sfp) != in_len) {
        free(in);
        fclose(sfp);
        fclose(dfp);
        return -1;
    }
    fclose(sfp);

    uint8_t *out = NULL;
    size_t out_len = header.size;
    tsur_out(in, in_len, &out, &out_len);
    if (out != NULL) {
        fwrite(out, 1, out_len, dfp);
        free(out);
    }
    fclose(dfp);
    free(in);
    return 1;
}
