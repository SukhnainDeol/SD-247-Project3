/**
 * @file board_structs.h
 * @author Sukhnain Deol 
 * @date 2024-02-19
 * @brief The file creates structure for the coordinates on the board used in the battleship game implemented in battleship.c. 
 *        It also creates a structure for the ships placed on the board in the same file.
 */


#pragma once

#include <stdbool.h>

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