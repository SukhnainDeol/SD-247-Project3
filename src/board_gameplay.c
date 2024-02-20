#include "../include/board_gameplay.h"


void displayBoard(char board[BOARD_SIZE][BOARD_SIZE], bool showShips)
{
    // print row header numbering  
    printf("  "); // top left board space
    for (int i = 0; i < BOARD_SIZE; i++) { printf("%d ", i); }
    printf("\n");

    // print each row 
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        printf("%d ",i); // row numbering
        for (int j = 0; j < BOARD_SIZE; j++) 
        { 
            // don't show ships if false
            if (!showShips && board[i][j] == 'S') 
            { 
                putchar(EMPTY_VALUE);
                putchar(' ');
                continue;
            }
            printf("%c ", board[i][j]); 
        }
        printf("\n"); 
    }
}


char guess(char board[BOARD_SIZE][BOARD_SIZE], Coordinate guess)
{
    if (!isValidGuess(board, guess)) { return -1; }

    switch (board[guess.y][guess.x])
    {
        case EMPTY_VALUE:
            board[guess.y][guess.x] = MISS_VALUE;
            return MISS_VALUE;
        case SHIP_VALUE:
            board[guess.y][guess.x] = HIT_VALUE;
            return HIT_VALUE;
        default:
            return 0;
    }
}


int updateShipsSunk(char board[BOARD_SIZE][BOARD_SIZE], Ship ships[NUM_SHIPS])
{
    int newShipsSunk = 0;
    for (int i = 0; i < NUM_SHIPS; i++)
    {
        if (hasSank(board, ships[i]) && !ships[i].isSunk) // something wrong here on last loop
        {
            ships[i].isSunk = true;
            newShipsSunk++;
        }
    }
    return newShipsSunk;
}


void takeTurn(char board[BOARD_SIZE][BOARD_SIZE], Ship ships[NUM_SHIPS], bool isPlayerTurn)
{
    Coordinate guessCoord;
    // get player input coordinates
    if (isPlayerTurn)
    {
        while (true)
        {
            printf("Enter Guess x-coordinate: ");
            scanf(" %d", &guessCoord.x);            
            printf("Enter Guess y-coordinate: ");
            scanf(" %d", &guessCoord.y);
            
            if (isValidGuess(board, guessCoord)) { break; }
            printf("ERROR: Invalid Input, Try again.\n");

            while (getchar() != '\n'); // clear input buffer
        }
        printf("\nPlayer "); // specify side in hit/miss notification below
    }

    // generate computer coordinates
    if (!isPlayerTurn)
    {
        while (true)
        {
            srand(time(NULL));
            guessCoord.x = rand() % 10;
            guessCoord.y = rand() % 10;

            if (isValidGuess(board, guessCoord)) { break; }
        }
        printf("Computer "); // specify side in hit/miss notification below
    }
        
    // apply guess and check for new ships sunk
    char coordValue = guess(board, guessCoord);
    int newShipSunk = updateShipsSunk(board, ships);

    // announce result
    if (coordValue == HIT_VALUE && newShipSunk) { printf("Sunk a Ship!\n"); }
    else if (coordValue == HIT_VALUE) { printf("Hit a Ship!\n"); }
    else if (coordValue == MISS_VALUE) { printf("Missed!\n"); }

    return;
}