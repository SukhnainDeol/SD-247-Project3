#ifndef BOARD_STRUCTS.H
#define BOARD_STRUCTS.H 

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


#endif