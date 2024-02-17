#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

#define SHIP_VALUE 'S'
#define HIT_VALUE 'H'
#define MISS_VALUE 'O'
#define BOARD_SIZE 10
#define NUM_SHIPS 5
#define SHIP_LENGTHS \
  {                  \
    5, 4, 3, 3, 2    \
  }

typedef struct
{
  int x;
  int y;
} Coordinate;

typedef struct
{
  Coordinate start;
  Coordinate end;
  int length;
  bool isSunk;
} Ship;

void initializeBoard(char board[BOARD_SIZE][BOARD_SIZE])
{
    // set each board value to '.'
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            board[i][j] = '.';
        }
    }
}

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
            if (!showShips && board[i][j] == 'S') { printf('.'); }
            printf("%c ", board[i][j]); 
        }
        printf("\n"); 
    }
}

/**
 * @brief validates whether the given space on a board is ok to place a ship at
 * checking for valid coordinate and already present ships.
 * 
 * @param board - board to check
 * @param start - start coord of ship
 * @param end - end coord of ship
 * @return true - is valid to place ship
 * @return false - is not valid to place ship
 */
bool isValidPlacement(char board[BOARD_SIZE][BOARD_SIZE], Coordinate start, Coordinate end)
{
    // validate start and end positions
    if (!isValidGuess(board, start) || !isValidGuess(board, end)) { return false;}

    // check for already-present ships
    int xCoord = abs(start.x - end.x);
    int yCoord = abs(start.y - end.y);
    int distance = xCoord + yCoord;

    for (int i = distance; i <= 2*distance; i++)
    {
        char coordValue;
        if (yCoord == 0) { coordValue = board[i][start.y]; }
        else if (xCoord == 0) { coordValue = board[start.x][i]; }
        else { return false; }

        // check if ship
        if (coordValue == SHIP_VALUE) { return false; }
    }
    return true;
}

/**
 * @brief checks if coordinate on a board has been guessed before
 * by checking if it was a hit or miss.
 * 
 * @param board - board to be checked
 * @param guess - guess coordinates
 * @return true - coord has not been guessed
 * @return false - coord has been guessed
 */
bool isGuessed(char board[BOARD_SIZE][BOARD_SIZE], Coordinate guess)
{
    return board[guess.x][guess.y] == HIT_VALUE || board[guess.x][guess.y] == MISS_VALUE;
}

bool isSunk(char board[BOARD_SIZE][BOARD_SIZE], Ship ship)
{
    // check if the ship is sunk
}

/**
 * @brief Checks a given coordinate on a board to see if value 
 * can be guess by players. Meaning it hasn't been guessed and is
 * in the board's range.
 * 
 * @param board - board to check guess on
 * @param guess - x,y coordinate of guess
 * @return true - guessable coordinate
 * @return false - value has been guessed or out of range
 */
bool isValidGuess(char board[BOARD_SIZE][BOARD_SIZE], Coordinate guess)
{
    // guess coords are 0 - 10 and haven't been guessed
    if (!(guess.x < BOARD_SIZE && guess.x >= 0 &&
     guess.y < BOARD_SIZE && guess.y >= 0) ||
     isGuessed(board, guess)) 
    { 
        return false;
    }
    return true;
}

void placeShip(char board[BOARD_SIZE][BOARD_SIZE], Ship ship)
{
    // get random coordinates
    // check if valid placement
    // repeat until placed
}

void takeTurn(char board[BOARD_SIZE][BOARD_SIZE], Ship ships[NUM_SHIPS], bool isUserTurn)
{
    // logic for a turn (user or computer)
}

bool isGameOver(Ship ships[NUM_SHIPS])
{
    // is the game over?
}

int main()
{
    // initalize boards
    char playerBoard[BOARD_SIZE][BOARD_SIZE];
    char computerBoard[BOARD_SIZE][BOARD_SIZE];
    initializeBoard(playerBoard);
    initializeBoard(computerBoard);

    displayBoard(playerBoard, true);


    // init player & computer board

    // game loop begin

    // display both boards
        // computer board should only show hits and misses

    // get guesses
        // ask user for guess (validate)
        // generate computer guess (validate)

    // apply guesses
        // send players hit, miss, ship sunk message

    // when game is over

    // announce who won
}
