/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include <stdio.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int array[], int n)
{
    for (int i = 0; i < n; i++)
    {
        if (array[i] == value) 
        {
            return true;
        }
    }
    return false;
}

/**
 * Sorts array of n values at O(n) 
 */
void sort(int values[], int n)
{
    int valuesMulti[n][5];
    // Radix sort
    
    // split the numbers
    for (int i = 0; i < n; i++)
    {
        int j = 0;
        printf("Value: %i\n", values[i]);

        while (values[i] > 0){
            valuesMulti[i][j] = values[i] % 10;
            values[i] /= 10;
            printf("valuesmulti %i\n", valuesMulti[i][j]);
            j++; 
        }
        printf("\n");
    }

    // Dump them in buckets
    // int buckets[9][n];
    for (int i = 0; i < n; i++)
    {
    }


    return;
}