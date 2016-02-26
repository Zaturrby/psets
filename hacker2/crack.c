#include <stdio.h>
#define _XOPEN_SOURCE
#include <unistd.h>
#include <string.h>
// #include <crypt.h>

// crack.c is a program that cracks fake old UNIX passwords

int checkPassword(char * password, char * hash)
{   
    int modifier;
    char salt[3] = {32, 32};
    char * passwordHash;
    
    // Generate all possible salts and test them with crypt

    // This part actually might be neater as a recursive function too
    // This works for two levels of nesting, 
    // although I already have code duplication (not DRY)
    for (int i = 0; i < 64; i++)
    {
        // i to ascii mapping for salt
        if (i >= 38) {
            modifier = 59;
        } else if ( i >= 12) {
            modifier = 53;
        } else if ( i >= 0) {
            modifier = 46;
        }
        salt[0] = modifier + i;
        
        for (int j = 0; j < 64; j++)
        {
            // i to ascii mapping for salt
            if (j >= 38) {
                modifier = 59;
            } else if ( j >= 12) {
                modifier = 53;
            } else if ( j >= 0) {
                modifier = 46;
            }
            salt[1] = modifier + j;
            
            // Encrypt with the generated salt and test wether the hashes
            // are equal.
            passwordHash = crypt(password, salt);
            if (!strcmp(hash, passwordHash))
            {
                return 0;
            }
        }
    }

    // This little thing already has the right salt (50) hardcoded, 
    // saves quite a bit of effort while testing

    // char * passwordHash = crypt(password, "50");
    // if (!strcmp(hash, passwordHash))
    // {
    //     return 0;
    // }

    return 1;
}

int generatePasswordandCheck(int position, int length, char password[8], char * hash)
{
    /* 
    A note to the wise:

    32 < 127 are the required chars, yet 48 < 54 (range [0-5]) were already 
    quite the hassle for my dear ol' machine. The hash "50Bpa7n/23iug"
    (password: 12345) takes 55 seconds to solve on my machine with the 
    short range... With the full range however, and 8 characters as the 
    assignment requires, it would take a bit longer with this code. 
    My estimate yielded about 1.4 million years. 

    Somehow, i think, that can be done faster.
    */
    
    // loop over all the range of ascii characters 
    for (int m = 32; m < 127; m++) 
    {
        // Change the letter in the current position
        password[position] = m;

        // Only check the lowest recursion to not "greatly perturb" doubles
        if (position == length - 1 && !checkPassword(password, hash))
        {
            printf("%.*s\n", length, password);
            return 0;

        // The recursive part with an exit conditional
        } else if (position < length - 1) 
        {
            if (!generatePasswordandCheck(position + 1, length, password, hash))
            {
                return 0;
            };
        }
    }
    return 1;
}

int main(int argc, char * argv[])
{
    // hardcoded test hash
    // char * hash = "50Bpa7n/23iug"; // solves to 12345

    // getting the hash and erroring when needed
    if (argc == 1 || argc > 2){
        return 1;
    }
    char * hash = argv[1];

    // define maxlength for checking and initial password
    int maxLength = 8;
    char initialPassword[maxLength]; 
    
    // loop over all possible lengths and quit when password is found
    int found = 1;
    int passwordLength = 1;

    while (passwordLength <= maxLength && found == 1)
    { 
        found = generatePasswordandCheck(0, passwordLength, initialPassword, hash);
        passwordLength++;
    }

    if (found == 0){
        return 0;
    } else {
        return 1;
    }

}