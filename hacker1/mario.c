#include <stdio.h>
#include <cs50.h>

int main(void)
{   
    int height;
    do 
    {
        printf("Height: ");
        height = GetInt();
    } while (height < 0 || height > 23);

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; (j+1) < (height - i); j++)
        {
            printf(" ");        
        }
        for (int j = 0; j < i + 1; j++)
        {
            printf("#");        
        }
        printf("  ");
        for (int j = 0; j < i + 1; j++)
        {
            printf("#");        
        }
        printf("\n"); 
    }
}