/**
 * @file board_validation.h
 * @author Sukhnain Deol 
 * @date 2024-02-19
 * @brief This file provides validation functions for validating data from ships from the board_struct.h file and boards. 
 *        Both of which are used in the battleship.c file. The file uses functions from the board_gameplay which itself validates gameplay structures and arrays from this file.
 */

#pragma once

#include "board_macros.h"
#include "board_structs.h"
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>


/**
 * @brief checks if coordinate on a board has been guessed before
 * by checking if it was a hit or miss.
 * 
 * @param board - board to be checked
 * @param guess - guess coordinates
 * @return true - coord has not been guessed
 * @return false - coord has been guessed
 */
bool isGuessed(char board[BOARD_SIZE][BOARD_SIZE], Coordinate guess);


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
bool isValidGuess(char board[BOARD_SIZE][BOARD_SIZE], Coordinate guess);


/**
 * @brief Checks the segments of a ship on a board to see if it is sunk
 * 
 * @param board - board of ship to check
 * @param ship - ship struct to check if sunk
 * @return true - all ship segments are sunk
 * @return false - not all ship segments are sunk
 */
bool hasSank(char board[BOARD_SIZE][BOARD_SIZE], Ship ship);


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
bool isValidPlacement(char board[BOARD_SIZE][BOARD_SIZE], Coordinate start, Coordinate end);


/**
 * @brief if all ships are sunk, game is over
 * 
 * @param ships - arr of board's ships structs
 * @return true - game is over
 * @return false - game is not over
 */
bool isGameOver(Ship ships[NUM_SHIPS]);