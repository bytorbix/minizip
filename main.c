#include <stdio.h>
#include "rle.h"
#include "io.h"
#include <string.h>

int main(int argc, char *argv[]) {
    // valid arguments amount passed
    if (argc == 4)
    {
        char *action = argv[1];
        char *src_path = argv[2];
        char *dest_path = argv[3];

        if (strcmp(action, "compress") == 0) {
            if (tsuridity(src_path) && tsuridity(dest_path)) {
                int flag = tsur_compress(src_path, dest_path);
                if (flag == 1) {
                    printf("%s was compressed into %s\n", extract_filename(src_path), extract_filename(dest_path));
                }
            }
        }
    }
    else {
        printf("Invalid Argument!\n");
        return -1;
    }
    return 0;
}
