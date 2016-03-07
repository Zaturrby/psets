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
#include <math.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool linearSearch(int value, int array[], int n)
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
 * Recursive binary search
 */
int searchR(int value, int array[], int nmin, int nmax)
{
    // check to go on
    if (nmax - nmin == 0)
    {
        return false;
    }

    // determine average
    int navg = ((nmax - nmin) / 2) + nmin;

    // recursive boolean search
    if (array[navg] == value)
    {
        return true;
    } else if (array[navg] > value)
    {
        return searchR(value, array, nmin, navg);
    } else if (array[navg] < value)
    {
        return searchR(value, array, navg + 1, nmax);
    }

    // should never happen
    return false;
}

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int array[], int n)
{
    return searchR(value, array, 0, n);
}

/**
 * Sorts array of n values at O(n)
 *
 * Radix sort O(5n) is implemented which runs in linear time.
 * However it is actually slower than merge sort until n = 500.000
 * In my implementation probably even later, but hey, it's linear!
 *
 * What I should have done is choose merge sort until n = 19870 
 * and then followed up on that with counting sort O(n+65536), 
 * which has the least amount of operations from n = 19870.
 * And, not to forget, I should probably simplify/refactor 
 * just a tad more. Might be poss
 */

void sort(int values[], int n)
{
    // radix sort
    for (int times = 0; times < 5; times++)
    {
        int buckets[10][n];
        int bucketsLength[10] = {0};
        
        // into the buckets
        for (int i = 0; i < n; i++)
        {
            int currentBucket = ((int) (values[i] / (1 * pow(10, times))) % 10);
            buckets[currentBucket][bucketsLength[currentBucket]] = values[i];
            bucketsLength[currentBucket]++;
        }

        // out of the buckets
        int bucketCount = 0;
        int i = 0;
        int j = 0; 
        while (bucketCount < 10)
        {
            if (bucketsLength[bucketCount] != 0)
            {
                values[i] = buckets[bucketCount][j];
                i++;
                j++;
            }
            if (bucketsLength[bucketCount] <= j)
            {
                bucketCount++;
                j = 0;
            }
        }
    }
    return;
}