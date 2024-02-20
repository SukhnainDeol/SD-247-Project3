#include "../include/game_init.h"


void initializeBoard(char board[BOARD_SIZE][BOARD_SIZE])
{
    // set each board value to '.'
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

    srand(time(NULL));

    while (true)
    {
        // get random start 
        start.x = rand() % BOARD_SIZE;
        start.y = rand() % BOARD_SIZE;

        // use random generator to get 0 or 1 to decide direction
        direction = rand() % 2;

        if (direction == 0) // 0 = horizontal
        {
            // -1 because .start is first length
            end.x = start.x + ship->length-1;
            end.y = start.y;
        }
        else // 1 = vertical
        {
            end.x = start.x; // -1 because .start is first length
            end.y = start.y + ship->length-1; 
        }
        
        if (isValidPlacement(board, start, end)) { break; }
    }

    // place ship locations in struct
    ship->start = start;
    ship->end = end;

    // place ships on board
    for (int i = 0; i < ship->length; i++)
    {
        int x = ship->start.x;
        int y = ship->start.y;
        // move based on direction of ships
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
