#include <stdio.h>
#include <unistd.h>

void main(void) 
{
    unsigned char count = 0;

    while(1) 
    {
        printf("And when you finally saw it come\n");
        printf("It passed you by\n");
        printf("And left you so defeated...\n");
        printf("\n");
        count++;

        if (count == 0xFF)
        {
            printf("You win!\n");
            return;
        }

        sleep(4);
    }
}