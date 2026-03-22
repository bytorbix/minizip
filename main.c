#include <stdio.h>

int main(int argc, char *argv[]) {
    (void)argc;
    (void)argv;

    printf("Program name is: %s", argv[0]);

    // valid arguments amount passed
    if (argc == 4)
    {
        char *action = argv[1];
        char *src_path = argv[2];
        char *dest_path = argv[3];

        // to be implemented
        if (valid_path(src_path) && valid_path(dest_path)) 
        {
            if (is_base(src_path)) {
                // access file from relative path
                if (is_base(dest_path)) {
                    // access dest file from relative path
                }
                // otherwise absolute path
            }
            // both absolute path
        }
        
        
    }

    return 0;
}
