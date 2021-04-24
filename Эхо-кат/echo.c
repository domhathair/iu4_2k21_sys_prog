#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int main(int argc, char* argv[]) {

    if (argc > 1) {

        if (argc > 2) {

            char* dir = (char*)malloc(sizeof(char) * 128);
            char* file_dir = "C:\\Users\\chepk\\Downloads\\";
            char* file_name = argv[1];
            char* mode = argv[2];
            char* string = "Hello, world with '010'.";
            FILE *file;

            strcpy(dir, file_dir);
            strcat(dir, file_name);

            //printf("Mode: %c\n", *mode);

            if ((*mode == 'w') && strlen(mode) < 2) {
                
                file = fopen(dir, "w+");
                printf("File created: %s\n", dir);
                fputs((const char*)string, file);
                printf("String added: \"%s\"\n", string);
                fclose(file);

            }
            else if ((*mode == 'd') && strlen(mode) < 2) {

                remove(dir);
                printf("File removed: %s\n", dir);
                return 0;

            } 
            else 
            printf("Allowed modes: \"w\" to create and \"d\" to remove.\n");

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