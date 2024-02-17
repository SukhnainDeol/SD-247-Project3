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


/**
 * @brief Takes a board of BOARD_SIZE x BOARD_SIZE and fills it with '.'
 * 
 * @param board - Board to initialize
 */
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


/**
 * @brief Prints the board to the user with an outline of row and column
 * numbers and the decision to hide or show the Ship Locations
 * 
 * @param board - board to display
 * @param showShips - whether to display SHIP_VALUE or to hide from player
 */
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
 * @param start - start coord of ship (start coord must be lower number)
 * @param end - end coord of ship
 * @return true - is valid to place ship
 * @return false - is not valid to place ship
 */
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


/**
 * @brief 
 * 
 * @param board 
 * @param ship 
 * @return true 
 * @return false 
 */
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


/**
 * @brief 
 * 
 * @param board 
 * @param ship 
 */
void placeShip(char board[BOARD_SIZE][BOARD_SIZE], Ship ship)
{
    // get random coordinates
    // check if valid placement
    // repeat until placed
}


/**
 * @brief 
 * 
 * @param board 
 * @param ships 
 * @param isUserTurn 
 */
void takeTurn(char board[BOARD_SIZE][BOARD_SIZE], Ship ships[NUM_SHIPS], bool isUserTurn)
{
    // logic for a turn (user or computer)
}


/**
 * @brief 
 * 
 * @param ships 
 * @return true 
 * @return false 
 */
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

    // makes ships arr for each team
    // place each ship in arr

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