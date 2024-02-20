/**
 * @file board_gameplay.h
 * @author Sukhnain Deol
 * @date 2024-02-19
 * @brief This file declares functions used in battleship.c's gameloop. Giving the functionality to 
 *        display the battleship boards, take and apply guesses from player & computer.
 */


#pragma once

#include "board_macros.h"
#include "board_structs.h"
#include "board_validation.h"
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>


/**
 * @brief Prints the board to the user with an outline of row and column
 * numbers and the decision to hide or show the Ship Locations
 * 
 * @param board - 2d array board to display
 * @param showShips - whether to display SHIP_VALUE or to hide when printed
 */
void displayBoard(char board[BOARD_SIZE][BOARD_SIZE], bool showShips);


/**
 * @brief Applys a guess to a board by changing the value of the coord
 * to hit or miss values based on if there is ship there. If guess is invalid
 * return -1
 * 
 * @param board - board guess is applied on
 * @param guess - guess coordinate for board
 * @return char - return miss or hit values to indicate result. Or -1 in error
 */
char guess(char board[BOARD_SIZE][BOARD_SIZE], Coordinate guess);


/**
 * @brief checks the ships on a board and updates their isSunk values and
 * returns the count of new ships sunk
 * 
 * @param board - board of ships
 * @param ships - arr of ships of board
 * @return int - number of new ships updated to sunk
 */
int updateShipsSunk(char board[BOARD_SIZE][BOARD_SIZE], Ship ships[NUM_SHIPS]);


/**
 * @brief plays a turn for either the computer or player and prints the result
 * 
 * @param board - board of player/computer currently playing
 * @param ships - ships of player/computer currently playing
 * @param isPlayerTurn - if player or computer's turn
 */
void takeTurn(char board[BOARD_SIZE][BOARD_SIZE], Ship ships[NUM_SHIPS], bool isPlayerTurn);