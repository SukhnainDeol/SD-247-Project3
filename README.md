# Compiling The Program

Enter the following into the command line from the project directory (*SukhnainDeol_Project3*):

``` gcc src/battleship.c src/game_init.c src/board_validation.c src/board_gameplay.c -I/include -o battleship ```

To run the program, enter:

` ./battleship `

# Gameplay

Once you've begun the game, your board which is fully-revealed and the computer's board will be displayed. Your prompted to enter the x-coordinate and then the y-coordinate of your guess. The round will proceed with both your guess and the computer's being applied to the board. You will be notified of the result of each side's guess and then the next round will begin. This cycle continues until one side destroys all 5 of the enemy's ships.

# Design Decisions & Methodology
