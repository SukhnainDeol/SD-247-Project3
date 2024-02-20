#include "../include/board_validation.h"


bool isGuessed(char board[BOARD_SIZE][BOARD_SIZE], Coordinate guess)
{
    return board[guess.y][guess.x] == HIT_VALUE || board[guess.y][guess.x] == MISS_VALUE;
}


bool isValidGuess(char board[BOARD_SIZE][BOARD_SIZE], Coordinate guess)
{
    // guess coords are 0 - 9 
    if (!(guess.x < BOARD_SIZE && guess.x >= 0 && guess.y < BOARD_SIZE && guess.y >= 0)) 
    { 
        return false;
    }
    // haven't been guessed
    else if (isGuessed(board, guess))
    {
        return false;
    }
    return true;
}


bool hasSank(char board[BOARD_SIZE][BOARD_SIZE], Ship ship)
{
    int sunkCount = 0;
    for (int i = 0; i < ship.length; i++)
    {
        char coordValue;
        // increments coordinates based on if ship is horizontal or vertical (x or y is same)
        if (ship.start.x == ship.end.x) { coordValue = board[ship.start.x][ship.start.y + i]; }
        else if (ship.start.y == ship.end.y) { coordValue = board[ship.start.x + i][ship.start.y]; }

        if (coordValue == HIT_VALUE) { sunkCount++; }
    }

    if (sunkCount == ship.length) { return true; }
    return false;
}


bool isValidPlacement(char board[BOARD_SIZE][BOARD_SIZE], Coordinate start, Coordinate end)
{
    // validate start and end positions
    if (!isValidGuess(board, start) || !isValidGuess(board, end)) { return false;}

    // calculate size of ship (distance)
    int xCoord = abs(start.x - end.x);
    int yCoord = abs(start.y - end.y);
    int distance = xCoord + yCoord;

    // check each coordinate of ship
    for (int i = 0; i <= distance; i++)
    {
        char coordValue;
        // if horizontal
        if (yCoord == 0) { coordValue = board[start.x + i][start.y]; }
        // if vertical
        else if (xCoord == 0) { coordValue = board[start.x][start.y + i]; }
        else { return false; }

        // check if ship
        if (coordValue == SHIP_VALUE) { return false; }
    }
    return true;
}


bool isGameOver(Ship ships[NUM_SHIPS])
{
    for (int i = 0; i < NUM_SHIPS; i++)
    {
        if (!ships[i].isSunk) { return false; }
    }
    return true;
}
