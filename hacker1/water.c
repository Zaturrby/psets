#include <stdio.h>
#include <cs50.h>

int main(void)
{   
    int time;
    do {
        printf("minutes: ");
        time = GetInt();
    } while (time <= 0);
    
    int bottle = time * 12;
    printf("bottles: %i \n", bottle);
}