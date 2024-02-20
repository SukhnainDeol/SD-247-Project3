#pragma once

#include "board_macros.h"
#include "board_structs.h"
#include "board_validation.h"
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

/**
 * @brief Takes a board of BOARD_SIZE x BOARD_SIZE and fills it with '.' (EMPTY_VALUE)
 * 
 * @param board - Board to initialize
 */
void initializeBoard(char board[BOARD_SIZE][BOARD_SIZE]);


/**
 * @brief place a ship randomly on a board, validating to make sure
 * there are no ship collisions or the ship going off board
 * 
 * @param board - board arr to place on
 * @param ship - ship struct to place
 */
void placeShip(char board[BOARD_SIZE][BOARD_SIZE], Ship *ship);


/**
 * @brief adds ship lengths to each ship in arr and places ships on board
 * 
 * @param board - board to place ships on
 * @param ships - arr of ships to place
 */
void initializeShips(char board[BOARD_SIZE][BOARD_SIZE], Ship ships[NUM_SHIPS]);