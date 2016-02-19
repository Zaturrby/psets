#include <stdio.h>
#include <cs50.h>
#include <math.h>
  
int main(void)
{   
    printf("Please enter a creditcard number:");
    long long creditCard = GetLongLong();
    
    // int to array conversion
    // simplified and adapted version of the function provided by: 
    // http://stackoverflow.com/questions/515612/convert-an-integer-number-into-an-array
    int creditCardLength =  (int)floor(log10((float)creditCard)) + 1;
    int creditCardArr[creditCardLength];
    int creditCardArrInverse[creditCardLength];
    int i = 0;
    do {
        creditCardArr[i] = creditCard % 10;
        creditCardArrInverse[creditCardLength - i - 1] = creditCard % 10;
    	creditCard /= 10;
    	i++;
    } while (creditCard != 0);
    // end stackoverflow
    
    
    // The counting algorithm
    int sumEven = 0;
    int sumOdd = 0;
    for (int j = 0; j < creditCardLength; j++) {
        if (j % 2 == 0){
            sumEven += creditCardArr[j];
        } else {
            sumOdd += ((creditCardArr[j]*2) / 10) % 10;
            sumOdd += (creditCardArr[j]*2) % 10;
        }        
    }
    int sumTotal = sumOdd + sumEven;
    
    
    // Company checks
    if (sumTotal % 10 == 0){
        if (
            creditCardLength == 15 && 
            creditCardArrInverse[0] == 3 && (
                creditCardArrInverse[1] == 4 || 
                creditCardArrInverse[1] == 7
            )) {
            printf("AMEX\n");
        } else if (
            creditCardLength == 16 && 
            creditCardArrInverse[0] == 5 && (
                creditCardArrInverse[1] == 1 || 
                creditCardArrInverse[1] == 2 ||
                creditCardArrInverse[1] == 3 ||
                creditCardArrInverse[1] == 4 ||
                creditCardArrInverse[1] == 5
            )) {
            printf("MASTERCARD\n");
        } else if ((creditCardLength == 13 || creditCardLength == 16) && creditCardArrInverse[0] == 4) {
            printf("VISA\n");
        } else {
            printf("INVALID\n");
        }
    } else {
        printf("INVALID\n");
    }
}