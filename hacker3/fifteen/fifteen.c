/**
 * fifteen.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

// inversions
int inv;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = GetInt();

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(500000);
    }

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Algorithm to sort ánd to count inversions to the global scope
 * 
 * Global scope is a quick fix to avoid having to use somekind of
 * struct as output of the function, which holds the array and 
 * the inversion count
 */
int * countInversions(int arr[], int n){
    printf("-> in %i\n", n);
    if (n > 1) 
    {   
        // enter recursion
        int leftArr[n/2];
        int rightArr[(int)ceil(n/2)];
        for (int i = 0; i < n; i++)
        {
            // printf("%i - loop\n", n);
            if (i < (int)(n/2))
            {
                leftArr[i] = arr[i];
            } else {
                rightArr[(int)ceil(i-n/2)] = arr[i];
            }
        }
        countInversions(leftArr, n/2);
        countInversions(rightArr, ceil(n/2));
    
        // printf("pass!!\n\n\n");
        
        printf("**********left\n");
        for (int i = 0; i < n/2; i++)
        {
            printf("item: %i\n", leftArr[i]);
        }

        printf("**********right\n");
        
        for (int i = 0; i < ceil(n/2); i++)
        {
            printf("item: %i\n", rightArr[i]);
        }
        printf("**********end\n");

        // merge
        // printf("------merging------- %i\n", n/2);
        int left = 0;
        int right = 0;
        for (int i = 0; i < n; i++)
        {
            if (left < n/2 && right < ceil(n/2))
            {
                if (leftArr[left] > rightArr[right])
                {
                    // printf("**i=%i** rightvalue ->%i<- right %i \n", i, rightArr[right], right);
                    arr[i] = rightArr[right];
                    right++;
                } else {
                    // printf("**i=%i** leftvalue ->%i<- left %i \n", i, leftArr[left], left);
                    arr[i] = leftArr[left];
                    left++;
                    inv += right;
                }
            } else if (right < ceil(n/2)) 
            {
                arr[i] = rightArr[right];
                right++;
            } else 
            {
                arr[i] = leftArr[left];
                left++;
                inv += right;
            }

        }
        printf("&&&&&&&& invcount: %i &&&&&&&&&&&&\n", inv);

        // printf("------done-------\n");

    }

    // printf("---------------------\n");
    // for (int i = 0; i < n; i++)
    // {
    //     printf("item: %i\n", arr[i]);
    // }
    // printf("---------------------\n");


    printf(" <- out %i\n", n);
    return arr;
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).  
 */
void init(void)
{
    // int n = d * d;
    // get array of d*d size with ordered numbers
    // int blocks[n];
    // for (int i = 0; i < n; i++)
    // {
    //     blocks[i] = i;
    // }

    // shuffle - Fisher-Yates modern version
    // https://en.wikipedia.org/wiki/Fisher%E2%80%93Yates_shuffle
    // srand48(50);
    // for (int i = n - 1; i > 0; i--)
    // {
    //     int j = drand48() * i;
    //     int temp = blocks[j];
    //     blocks[j] = blocks[i];
    //     blocks[i] = temp;
    // }
    
    // int blocks[16] = {12, 1, 10, 2, 7, 11, 4, 14, 5, 16, 9, 15, 8, 13, 6, 3};
    int blocks[16] = {13, 10, 11, 6, 5, 7, 4, 8, 1, 12, 14, 9, 3, 15, 2};

    /** 
     * make sure the board is solvable by counting inversions
     * and applying the following formula:
     *
     * a. If the grid width is odd, then the number of inversions in a solvable 
     * situation is even.
     * b. If the grid width is even, and the blank is on an even row counting 
     * from the bottom (second-last, fourth-last etc), then the number of inversions 
     * in a solvable situation is odd.
     * c. If the grid width is even, and the blank is on an odd row counting from 
     * the bottom (last, third-last, fifth-last etc) then the number of inversions 
     * in a solvable situation is even.
     * 
     * Credits:
     * https://www.cs.bham.ac.uk/~mdr/teaching/modules04/java2/TilesSolvability.html
     */

    // int * sortedArray = countInversions(blocks, d*d);
    inv = 0;
    countInversions(blocks, d*d);

    // for (int i = 0; i < n; i++) {
    printf("sorted with %i inversions\n\n", inv);
        // printf("sorted: %i \n", sortedArray);
    // }
    usleep(5000000);

    // Put blocks to the board (multidimensional array)
    int k = 0;
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++, k++)
        {
            board[i][j] = blocks[k];
        }
    }
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    for (int i=0; i < d; i++)
    {
        for (int j=0; j < d; j++)
        {
            if (board[i][j] < 10)
            {
                printf(" ");
            }
            printf("%i   ", board[i][j]);
        }
        printf("\n\n");
    }
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{
    // find coordinates:
    int zpos[2] = {d, d};
    int tpos[2] = {d, d};
    for (int i=0; i < d; i++)
    {
        for (int j=0; j < d; j++)
        {
            if (board[i][j] == 0){
                zpos[0] = i;
                zpos[1] = j;
            }
            if (board[i][j] == tile){
                tpos[0] = i;
                tpos[1] = j;
            }
        }
    }

    // Swap if distance is 1
    // Illegal moves impossible: initial positions are larger than the board
    int distance = ceil(sqrt(pow((zpos[0] - tpos[0]), 2) + pow((zpos[1] - tpos[1]), 2)));
    if (distance == 1){
        board[zpos[0]][zpos[1]] = board[tpos[0]][tpos[1]];
        board[tpos[0]][tpos[1]] = 0;
        return true;
    } 

    return false;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
    // Covert to single dimension
    int blocks[d*d];
    int k = 0; 
    for (int i=0; i < d; i++)
    {
        for (int j=0; j < d; j++, k++)
        {
            blocks[k] = board[i][j];
        }
    }

    // Check
    for (int i=0; i < d*d - 1; i++){
        if (!(blocks[i] + 1 == blocks[i+1]))
        {   
            return false;
        }
    }

    return true;
}