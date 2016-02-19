#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{   
    float cash;
    do 
    {
        printf("Cash: \n");
        cash = GetFloat();
    } while ( cash < 0);
    
    
    // float coinTypes[13] = {500, 200, 100, 50, 20, 10, 5, 2, 1, 0.25, 0.10, 0.05, 0.01};
    float coinTypes[4] = {0.25, 0.10, 0.05, 0.01};
    
    // Some array length codestealing from Stackoverflow going on here
    int coinTypesLength =  (sizeof(coinTypes)/sizeof(coinTypes[0])); 
    // Stop codestealing -> It seems to be quite sensible. 
    
    // printf("length: %i \n", coinTypesLength);
    int coinsDispensed[coinTypesLength];
    float result = 0.0;
    float remainder = 0.0;
    int total = 0;
    
    for (int i = 0; i < coinTypesLength; i++)
    {
        result = cash / coinTypes[i];    
        coinsDispensed[i] = result;
        total += result;
        // Idea with due credit to stackoverflow and manual pages
        remainder = fmod(result, 1.0);
        // end wonderfull stackoverflow idea
        cash = remainder * coinTypes[i];
        // printf("Paper or coin of type: %f is handed out: %i \n", coinTypes[i], coinsDispensed[i]);
    }
    printf("%i\n", total);
}