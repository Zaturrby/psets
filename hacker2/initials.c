#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

// initials.c is a program that asks for a name, and outputs the initials.
int main(void)
{
    string name = GetString();
    int stringLength = strlen(name);
    
    for (int i = 0; i < stringLength; i++)
    {
        // ignore spaces and output the next alphabetical character as a capital
        if (isspace(name[i]))
        {
            if (isalpha(name[i + 1]))
            {
                printf("%c", toupper(name[i + 1]));   
            }
        // Cornercase for i = 0
        } else if ( i == 0 ) 
        {
            if (isalpha(name[i])) 
            {
                printf("%c", toupper(name[i]));
            }
        }
    }
    printf("\n");
}