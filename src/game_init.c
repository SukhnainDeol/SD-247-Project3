/**
 * @file game_init.c
 * @author Sukhnain Deol
 * @brief This file defines functions declared in game_init.h, see that file for more info.
 * @date 2024-02-19
 */


#include "../include/game_init.h"


void initializeBoard(char board[BOARD_SIZE][BOARD_SIZE])
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            board[i][j] = EMPTY_VALUE;
        }
    }
}


void placeShip(char board[BOARD_SIZE][BOARD_SIZE], Ship *ship)
{
    Coordinate start;
    Coordinate end;
    int direction;

    while (true)
    {
        start.x = rand() % BOARD_SIZE;
        start.y = rand() % BOARD_SIZE;

        direction = rand() % 2;

        if (direction == 0) // 0 = horizontal
        {
            // -1 because .start is first length
            end.x = start.x + ship->length-1;
            end.y = start.y;
        }
        else // 1 = vertical
        {
            end.x = start.x;
             // -1 because .start is first length
            end.y = start.y + ship->length-1; 
        }
        
        if (isValidPlacement(board, start, end)) { break; }
    }

    ship->start = start;
    ship->end = end;

    // place ship on board
    for (int i = 0; i < ship->length; i++)
    {
        int x = ship->start.x;
        int y = ship->start.y;
        // move based on direction of ship
        if (direction == 0) { x += i; }
        else if (direction == 1) { y+= i; }

        board[x][y] = SHIP_VALUE;
    }
}


void initializeShips(char board[BOARD_SIZE][BOARD_SIZE], Ship ships[NUM_SHIPS])
{
    int shipLengths[NUM_SHIPS] = SHIP_LENGTHS;
    for (int i = 0; i < NUM_SHIPS; i++) 
    { 
        ships[i].length = shipLengths[i]; 
        ships[i].isSunk = false;
    }
    for (int i = 0; i < NUM_SHIPS; i++) { placeShip(board, &ships[i]); }
}
