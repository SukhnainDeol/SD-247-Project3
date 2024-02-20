/**
 * @file board_gameplay.c
 * @author Sukhnain Deol
 * @brief This file defines functions declared in board_gameplay.h, see that file for more info.
 * @date 2024-02-19
 */


#include "../include/board_gameplay.h"


void displayBoard(char board[BOARD_SIZE][BOARD_SIZE], bool showShips)
{
    // print row header numbering  
    printf("  "); // top left board space
    for (int i = 0; i < BOARD_SIZE; i++) { printf("%d ", i); }
    printf("\n");

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        printf("%d ",i); // row numbering
        for (int j = 0; j < BOARD_SIZE; j++) 
        { 
            // don't show ships if showShips == false
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
        if (hasSank(board, ships[i]) && !ships[i].isSunk)
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

    if (isPlayerTurn)
    {
        while (true)
        {
            printf("Enter Guess x-coordinate: ");
            scanf(" %d", &guessCoord.x);
            while (getchar() != '\n');
            
            printf("Enter Guess y-coordinate: ");
            scanf(" %d", &guessCoord.y);
            while (getchar() != '\n');
            
            if (isValidGuess(board, guessCoord)) { break; }
            printf("Invalid Input: Enter a number from 0-9 that has NOT been guessed.\n");
        }
        printf("\nPlayer "); // specify side in hit/miss notification below
    }

    if (!isPlayerTurn)
    {
        while (true) // generate computer coordinates
        {
            srand(time(NULL));
            guessCoord.x = rand() % 10;
            guessCoord.y = rand() % 10;

            if (isValidGuess(board, guessCoord)) { break; }
        }
        printf("Computer "); // specify side in hit/miss notification below
    }
        
    char coordValue = guess(board, guessCoord);
    int newShipSunk = updateShipsSunk(board, ships);

    if (coordValue == HIT_VALUE && newShipSunk) { printf("Sunk a Ship!\n"); }
    else if (coordValue == HIT_VALUE) { printf("Hit a Ship!\n"); }
    else if (coordValue == MISS_VALUE) { printf("Missed!\n"); }

    return;
}