#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

// project header includes 
#include "include/board_macros.h"
#include "include/board_structs.h"

// TODO
    // consider creating seperate header file
        // and split up functions more
    // README.md
    // free memory?
    // remove extra printfs
    // problems
        // computer turn not working (likely fixed)
             // some error in updatingSunk when i = NUM_SHIPS - 1
        // test inputs
        // compile warnings
        // boards are the same
        // ships aren't being updated (use pointers & free)
    // switch x and y in code cuz reversed axis




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
    return board[guess.y][guess.x] == HIT_VALUE || board[guess.y][guess.x] == MISS_VALUE;
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


/**
 * @brief Takes a board of BOARD_SIZE x BOARD_SIZE and fills it with '.' (EMPTY_VALUE)
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
            board[i][j] = EMPTY_VALUE;
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
 * @brief Checks the segments of a ship on a board to see if it is sunk
 * 
 * @param board - board of ship to check
 * @param ship - ship struct to check if sunk
 * @return true - all ship segments are sunk
 * @return false - not all ship segments are sunk
 */
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


/**
 * @brief place a ship randomly on a board, validating to make sure
 * there are no ship collisions or the ship going off board
 * 
 * @param board - board arr to place on
 * @param ship - ship struct to place
 */
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
            end.x = start.x + ship->length;
            end.y = start.y;
        }
        else // 1 = vertical
        {
            end.x = start.x;
            end.y = start.y + ship->length;
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


/**
 * @brief adds ship lengths to each ship in arr and places ships on board
 * 
 * @param board - board to place ships on
 * @param ships - arr of ships to place
 */
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


/**
 * @brief Applys a guess to a board by changing the value of the coord
 * to hit or miss values based on if there is ship there. If guess is invalid
 * return -1
 * 
 * @param board - board guess is applied on
 * @param guess - guess coordinate for board
 * @return char - return miss or hit values to indicate result. Or -1 in error
 */
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


/**
 * @brief checks the ships on a board and updates their isSunk values and
 * returns the count of new ships sunk
 * 
 * @param board - board of ships
 * @param ships - arr of ships of board
 * @return int - number of new ships updated to sunk
 */
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


/**
 * @brief plays a turn for either the computer or player and prints the result
 * 
 * @param board - board of player/computer currently playing
 * @param ships - ships of player/computer currently playing
 * @param isPlayerTurn - if player or computer's turn
 */
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
            printf("ERROR: Invalid Input, Try again.");

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


/**
 * @brief if all ships are sunk, game is over
 * 
 * @param ships - arr of board's ships structs
 * @return true - game is over
 * @return false - game is not over
 */
bool isGameOver(Ship ships[NUM_SHIPS])
{
    for (int i = 0; i < NUM_SHIPS; i++)
    {
        if (!ships[i].isSunk) { return false; }
    }
    return true;
}

void printShips(Ship ships[NUM_SHIPS])
{
    for (int i = 0; i < NUM_SHIPS; i++)
    {
        printf("len %d \n", ships[i].length);
        printf("is Sunk =  %d \n", (ships[i].isSunk == false));
        printf("x1 %d \n", ships[i].start.x);
        printf("y1 %d \n", ships[i].start.y);
        printf("x2 %d \n", ships[i].end.x);
        printf("y2 %d \n\n", ships[i].end.y);

    }
}


int main()
{
    // initialize ships & boards
    char playerBoard[BOARD_SIZE][BOARD_SIZE];
    char computerBoard[BOARD_SIZE][BOARD_SIZE];
    initializeBoard(playerBoard);
    initializeBoard(computerBoard);

    Ship playerShips[NUM_SHIPS];
    Ship computerShips[NUM_SHIPS];
    initializeShips(playerBoard, playerShips);
    initializeShips(computerBoard, computerShips);

    int round = 1;

    while (true) // game loop start
    {
        printf("ROUND %d\n\n", round);

        printf("Your Board: \n");
        displayBoard(playerBoard, true);

        printf("Enemy Board: \n");
        displayBoard(computerBoard, true);

        // player & computer turns
        printf("\n");
        takeTurn(computerBoard, computerShips, true);
        takeTurn(playerBoard, playerShips, false);
        printf("\n");

        round++;

        printShips(playerShips);
        printShips(computerShips);
        if (isGameOver(playerShips)) 
        { 
            printf("Computer Won!");
            break; 
        }
        else if (isGameOver(computerShips))
        {
            printf("You Won!");
            break;
        }
    }
    return 0;
}