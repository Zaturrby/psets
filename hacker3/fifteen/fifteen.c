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
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).  
 */
void init(void)
{
    int n = d * d;
    // get array of d*d size with ordered numbers
    int blocks[n];
    for (int i = 0; i < n; i++)
    {
        blocks[i] = i;
    }

    // shuffle - Fisher-Yates modern version
    // https://en.wikipedia.org/wiki/Fisher%E2%80%93Yates_shuffle
    srand48(50);
    for (int i = n - 1; i > 0; i--)
    {
        int j = drand48() * i;
        int temp = blocks[j];
        blocks[j] = blocks[i];
        blocks[i] = temp;
    }

    // make sure the board is solvable
    // TODO

    // Put them into a multidimensional array
    int k = 0;
    for (int i=0; i < d; i++)
    {
        for (int j=0; j < d; j++, k++)
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