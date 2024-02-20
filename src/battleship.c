#include <stdio.h>

// project header includes 
#include "../include/board_macros.h"
#include "../include/board_structs.h"
#include "../include/game_init.h"
#include "../include/board_validation.h"
#include "../include/board_gameplay.h"

// TODO
    // README.md
    // free memory?
    // Fix that boards are the same
    // switch x and y in code cuz reversed axis
    // file headers?
    // make notifications more visible

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
        displayBoard(computerBoard, false);

        // player & computer turns
        printf("\n");
        takeTurn(computerBoard, computerShips, true);
        takeTurn(playerBoard, playerShips, false);
        printf("\n");

        round++;

        // check for gameover
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
    // display fully-revealed boards
    printf("Your Board: \n");
    displayBoard(playerBoard, true);
    printf("Enemy Board: \n");
    displayBoard(computerBoard, true);

    return 0;
}