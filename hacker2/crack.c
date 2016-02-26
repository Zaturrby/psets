#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#define _XOPEN_SOURCE
#include <unistd.h>
#include <crypt.h>

// crack.c is a program that crash fake old UNIX passwords

int checkPassword(char * password, char * hash)
{
    int multiplier;
    char salt[3] = {32, 32};
    char * passwordHash;
    
    for (int i = 0; i < 64; i++)
    {
        // i to ascii mapping for salt
        if (i >= 38) {
            multiplier = 59;
        } else if ( i >= 12) {
            multiplier = 53;
        } else if ( i >= 0) {
            multiplier = 46;
        }
        salt[0] = multiplier + i;
        
        for (int j = 0; j < 64; j++)
        {
            // i to ascii mapping for salt - Not DRY
            if (j >= 38) {
                multiplier = 59;
            } else if ( j >= 12) {
                multiplier = 53;
            } else if ( j >= 0) {
                multiplier = 46;
            }
            salt[1] = multiplier + j;
            
            passwordHash = crypt(password, salt);
            if (!strcmp(hash, passwordHash))
            {
                printf("equal");
                return 0;
            }
        }
    }
    return 1;
}

char * recur(int position, int length, char password[8])
{
    // Change the asciicode of the 
    for (int m = 32; m < 36; m++) //127
    {
        password[position] = m;
        printf("\nposition: %i", position);
        printf("\npassword: >%.*s<", length, password);
        // printf("%i: >%.*s< ", m, length, password);
        // The recursive part
        if (position < length - 1)
        { 
            recur(position + 1, length, password);
        }
    }
    return "";
}

int main(void)
{
    // Initialize VLA to spaces (effective 0 in this case)
    int length = 3;
    char initialPassword[length]; 
    for(int i = 0; i < length; i++)
    {
        initialPassword[i] = 32;
    }
    
    char * password = recur(0, length, initialPassword);
    printf("\n\n"); 
}