#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int main(int argc, char* argv[]) {

    if (argc > 1) {

        if (argc > 2) {

            char* dir;
            char* file_dir = "C:\\Users\\chepk\\Downloads\\";
            char* file_name = argv[3];
            char* mode = argv[2];
            FILE *file;

            strcpy(dir, file_dir);
            strcat(dir, file_name);

            if (*mode == 'w' || *mode == 'r') {
                
                file = fopen(dir, mode);
                fclose(file);
                printf("File created: %s\n", dir);

            }
            else if (*mode == 'd') {

                remove(dir);
                printf("File removed: %s\n", dir);

            } 
            else 
            printf("Allowed modes: \"w+\" or \"r\" to create and \"d\" to remove.\n");

        }
        else {
            printf("Mode is not specified.\n");
            return -1;
        }
    }
    else {
        printf("File name is not specified.\n");
            return -1;
    }
    return 0;   
}