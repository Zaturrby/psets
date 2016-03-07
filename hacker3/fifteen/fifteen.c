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
#include <time.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

// inversions
int inv;

// moves
int moves;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
void godmode(void);
bool move(int tile);
bool won(void);
void randomSolution();
bool searchSolution(int boardcopy[], int depth, int pdirection);

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

    moves = 0;

    // Activate godmode
    // There still is some plumbing to be done (getInt() to get getString())
    // draw();
    // godmode();

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

        // // prompt for move
        printf("Tile to move: ");
        int tile = GetInt();

        // // move if possible, else report illegality
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
 * Algorithm to merge sort ánd to count inversions to the global scope
 */
int * countInversions(int arr[], int n)
{
    if (n > 1) 
    {   
        // enter recursion
        int leftArr[n / 2];
        int rightArr[(int) ceil(((float) n) / 2)];
        for (int i = 0; i < n; i++)
        {
            if (i < n / 2)
            {
                leftArr[i] = arr[i];
            } else 
            {
                rightArr[(int) ceil(i - (((float) n) / 2))] = arr[i];
            }
        }
        countInversions(leftArr, n / 2);
        countInversions(rightArr, (int) ceil(((float) n) / 2));
    
        // merge
        int left = 0;
        int right = 0;
        for (int i = 0; i < n; i++)
        {
            if (left < n / 2 && right < (int) ceil(((float) n) / 2))
            {
                if (leftArr[left] > rightArr[right])
                {
                    arr[i] = rightArr[right];
                    right++;
                } else 
                {
                    arr[i] = leftArr[left];
                    left++;
                    inv += right;
                }
            } else if (right < (int) ceil(((float) n ) / 2)) 
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
    }
    return arr;
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).  
 *  
 * The init follow the following steps:
 * 1. The init first generates an array of 0-15.
 * 2. Shuffle the array to a pseudorandom state seeded with the time
 * 3. Count inverions and substract the inversions caused by the zero
 * 4. Check if the board is solvable and adjust if needed **
 * 5. Put the array to the multidimensional array of the board
 *
 * ** To make sure the board is solvable by counting inversions
 * the following formula is applied:
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
void init(void)
{
    // get array of d*d size with ordered numbers
    int n = d * d;
    int blocks[n];
    for (int i = 0; i < n; i++)
    {
        blocks[i] = i;
    }

    // shuffle - Fisher-Yates modern version
    // https://en.wikipedia.org/wiki/Fisher%E2%80%93Yates_shuffle
    srand48((long int) time(NULL));
    for (int i = n - 1; i > 0; i--)
    {
        int j = drand48() * i;
        int temp = blocks[j];
        blocks[j] = blocks[i];
        blocks[i] = temp;
    }
    
    // Copy the array and find the 0;
    int blockscopy[n];
    int zeropos;
    for (int i = 0; i < n; i++)
    {
        blockscopy[i] = blocks[i];
        if (blocks[i] == 0){
            zeropos = i;
        } 
    }

    // Count the inversions in a global variable (inv) 
    // and subtract the inversions caused by the 0
    inv = 0;
    countInversions(blockscopy, d*d);
    inv -= zeropos;

    // Check if the board is solvable and fix it if need be
    // This 3-part condition is clearly described above
    if (!(((d % 2 != 0) && (inv % 2 == 0)) || 
        ((d % 2 == 0) && ((d - ((zeropos / d))) % 2 == 0) && (inv % 2 != 0)) ||
        ((d % 2 == 0) && ((d - ((zeropos / d))) % 2 != 0) && (inv % 2 == 0)) 
        ))
    {
        // Swaps the first inversion
        // Introducing a new one to change the parity is probably cleaner
        for (int i = 0; i < n; i++)
        {
            if ((blocks[i] > blocks[i + 1]) && (blocks[i] != 0 && blocks[i + 1] != 0)){
                int temp = blocks[i];
                blocks[i] = blocks[i + 1];
                blocks[i + 1] = temp;
                break;
            }
        }
    } 

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
    for (int i = 0; i < d*d - 1; i++){
        if (!(blocks[i] + 1 == blocks[i + 1]))
        {   
            return false;
        }
    }

    return true;
}

/**
 * Godmode for the game, where the player can sitback and watch
 * the puzzle get solved.
 */
void godmode(void)
{
    // Covert to single dimension
    int blocks[d * d];
    int k = 0; 
    for (int i=0; i < d; i++)
    {
        for (int j=0; j < d; j++, k++)
        {
            blocks[k] = board[i][j];
        }
    }

    // Start searching for the solution with a given depth in mind
    for (int i = 1; i < 30; i++){
        printf("\n\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\n");
        searchSolution(blocks, i, 10);
        printf("\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\n");
    }
}

/**
 * Recursively search for a solution.
 *
 * Currently not finished. There are quite a bit of debugging
 * statements in.
 *
 * TODO:
 * 1. Find where the terrible extra zero comes from
 * 2. Check if recursion finds a possible solution
 * 3. Optimize. 
 * 3.1. Find some way to sustain the tree while changing depth 
 * 3.2. Find some way to prioritize. (Priority queues??)
 *
 * Currently the functions follows these steps:
 * 1. Do not backtrack
 * 2. Create a copy of the board
 * 3. Move the block
 * 4. Go back to a array of single dimension
 * 5. Check wether victory has been achieved (currently not very DRY)
 * 6. Enter the recursion
 * 
 */
bool searchSolution(int blocks[], int depth, int pdirection)
{
    // Somewhere extra zeroes appear in the game...
    // Where-o-where do they come from?
    // Some debugging:
    int zerotest = 0;
    for (int i = 0; i < d * d; i++){
        if (blocks[i] == 0)
        {
            zerotest++;
        }
    }
    if (zerotest > 1){
        printf("*********More than one zero***********\n");
        usleep(2000000);
    }

    // Check to stop the recursion
    if (depth > 0){
        // No backtracking of the last move, quite pointless to explore those
        // recursions
        if (pdirection < 2)
        {
            pdirection += 2;
        } else {
            pdirection -= 2;
        }

        // For each possible direction
        for (int direction = 0; direction < 4; direction++)
        {
            // If attemt at backtracking cut it off
            if (direction == pdirection) {
                continue;
            }
            // Put the blocks to a boardcopy
            int boardcopy[d][d];
            int k = 0;
            int zpos[2] = {d, d};
            for (int i = 0; i < d; i++)
            {
                for (int j = 0; j < d; j++, k++)
                {
                    if (boardcopy[i][j] == 0){
                        zpos[0] = i;
                        zpos[1] = j;
                    }
                    boardcopy[i][j] = blocks[k];
                }
            }

            // Moves: one for each direction
            if (direction == 0 && zpos[0] < d - 1){
                boardcopy[zpos[0]][zpos[1]] = boardcopy[zpos[0] + 1][zpos[1]];
                boardcopy[zpos[0] + 1][zpos[1]] = 0;
            }
            if (direction == 1 && zpos[0] > 0) {
                boardcopy[zpos[0]][zpos[1]] = boardcopy[zpos[0] - 1][zpos[1]];
                boardcopy[zpos[0] - 1][zpos[1]] = 0;
            }
            if (direction == 2 && zpos[1] < d - 1){
                boardcopy[zpos[0]][zpos[1]] = boardcopy[zpos[0]][zpos[1]+1];
                boardcopy[zpos[0]][zpos[1] + 1] = 0;
            }
            if (direction == 3 && zpos[1] > 0) {
                boardcopy[zpos[0]][zpos[1]] = boardcopy[zpos[0]][zpos[1]-1];
                boardcopy[zpos[0]][zpos[1] - 1] = 0;
            }

            // All of this is only interesting if the direction allows a move
            if ((direction == 0 && zpos[0] < d - 1) ||
                (direction == 1 && zpos[0] > 0) || 
                (direction == 2 && zpos[1] < d - 1) || 
                (direction == 3 && zpos[1] > 0)) {

                // An easy measurement to count the number of tried moves
                moves++;
                if (moves % 10000000 == 0) {
                    printf("moves %i \n", moves);
                }
                // Covert boardcopy to an array of blocks
                int blockscopy[d*d];
                k = 0; 
                for (int i=0; i < d; i++)
                {
                    for (int j=0; j < d; j++, k++)
                    {
                        blockscopy[k] = boardcopy[i][j];
                    }
                }

                clear();

                // Print copy
                printf("Depth: %i, Direction: %i\n", depth, direction);
                for (int i = 0; i < d; i++)
                {
                    for (int j = 0; j < d; j++)
                    {
                        if (boardcopy[i][j] < 10)
                        {
                            printf(" ");
                        }
                        printf("%i   ", boardcopy[i][j]);
                    }
                    printf("\n\n");
                }

                // Check won
                int win = 1;
                for (int i = 0; i < d * d - 1; i++){
                    if (!(blockscopy[i] + 1 == blockscopy[i+1]))
                    {   
                        win = 0;
                    }
                }

                if (win == 1){
                    printf("\n***********************\n---WON---\n**********************\n");
                    usleep(2000000);
                }
                
                // Make the game followable
                usleep(500000);

                // Next move (recursive)
                searchSolution(blockscopy, depth - 1, direction);   
            }
        }
    }   
    return 0;
}