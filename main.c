#include <stdio.h>
#include "rle.h"
#include "io.h"
#include <string.h>

int main(int argc, char *argv[]) {
    // valid arguments amount passed
    if (argc ==3 || argc == 4)
    {
        char *action = argv[1];
        char *src_path = argv[2];
        char *dest_path = NULL;
        // Resolve dest_path
        if (argc == 4) {
            dest_path = argv[3];
        } 
        else if (strcmp(action, "compress") == 0) {
            dest_path = make_tsur(src_path);
        } 
        else if (strcmp(action, "decompress") == 0) {
            dest_path = kill_tsur(src_path);
            if (dest_path == NULL) {
                fprintf(stderr, "Error: Failed to process %s. "
                    "It may be unreadable or not a valid .tsur file.\n", src_path);
            }
        }
        // Run action
        if (dest_path != NULL && tsuridity(src_path) && (argc == 4 ? tsuridity(dest_path) : 1)) {
            if(strcmp(action, "compress") == 0) {
                tsur_compress(src_path, dest_path);
            }
            else if(strcmp(action, "decompress") == 0) {
                tsur_decompress(src_path, dest_path);
            }
            else {
                printf("Invalid Argument!\n");
                return -1;
            }
        }
    }
    else {
        printf("Invalid Argument!\n");
        return -1;
    }
    return 0;
}
