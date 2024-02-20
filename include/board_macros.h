/**
 * @file board_macros.h
 * @author Sukhnain Deol 
 * @date 2024-02-19
 * @brief This file defines relavent and reoccuring values in a battleship game implemented in the battleship.c
 */


#pragma once

#define EMPTY_VALUE '.'
#define SHIP_VALUE 'S'
#define HIT_VALUE 'H'
#define MISS_VALUE 'O'
#define BOARD_SIZE 10
#define NUM_SHIPS 5
#define SHIP_LENGTHS \
  {                  \
    5, 4, 3, 3, 2    \
  }
  