# Compiling The Program

Enter the following into the command line from the project directory (*SukhnainDeol_Project3*):

``` gcc src/battleship.c src/game_init.c src/board_validation.c src/board_gameplay.c -I/include -o battleship ```

Note: you can add `-Wall` after the `gcc` if you would like to see any additional errors. 

To run the program, enter:

` ./battleship `

# Gameplay

Once you've begun the game, your board, which is fully-revealed, and the computer's board will be displayed. You're prompted to enter the x-coordinate and then the y-coordinate of your guess. The round will proceed with both your guess and the computer's being applied to the board. You will be notified of the result of each side's guess and then the next round will begin. This cycle continues until one side destroys all 5 of the enemy's ships. (Note: You'll likely want to expand your console to see both boards and guess notifications more easily as they are relatively large.)

# Design Methodology

My methodology for developing this project was to plan out the individual parts I deemed necessary for the functionality of the game and develop the related parts together. Once each section, such as initalization, data validation, and gameplay are all completed, I would use the outline of the program requirements to put these pieces together in a main function. This is where I'd begin integration testing the functions as a whole system. In this process I'd utilize print functions that would relay the status of variables and structures during specific points in the program in order to debug.

# Design Decisions & Algorithms

The design of this game was to store the board in a 2-dimensional array which holds each position's state. And the ships themselves are written on board but they are also stored as separate structures which allows for easy access of each ship's status on the board. These two pieces, the board and the ship struct, are the basis of the game. Most algorithms used to validate data and apply player guesses in the game are based around accessing the board and reading states of specific positions. And any others are likely accessing data the array of ship structures for each board, one example of this is the algorithm to detect whether the game has finished. This algorithm reads the `isSunk` field of each ships of both players to see if one side's ships have all been sank.