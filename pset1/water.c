#include <stdio.h>
#include <cs50.h>

int main(void)
{   
    printf("minutes: ");
    int time = GetInt();
    int bottle = time * 12;
    printf("bottles: %i \n", bottle);
}