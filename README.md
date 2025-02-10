# InSem1Project

### Group Name: Pixels

<br>

### Student 1: Dia Pitroda
### Student Id: 202404009

<br> 

### Student 2: Vadi Quincy Hiren
### Student Id: 202401488

<br>

### Student 3: Sania Debbarma
### Student Id: 202404037

<br>


# "Snake Game"

# Snake Game - C++ Implementation

## Table of Contents
- [Overview](#overview)
- [Features](#features)
- [Game Controls](#game-controls)
- [Code Explanation](#code-explanation)
- [Compiling and Running the Game](#compiling-and-running-the-game)
- [Screenshots](#screenshots)
- [Conclusion](#conclusion)
- [License](#license)

## Overview
This is a simple implementation of the classic Snake game in C++ using the Windows console. The game features a snake that moves around the screen, eating food to grow longer, while avoiding collisions with itself and the walls. The player controls the snake using the keyboard keys W, A, S, and D for up, left, down, and right respectively.

## Features
- **Snake Movement**: The snake moves in four directions: Up, Down, Left, and Right.
- **Food Generation**: Random food is spawned on the board, and the snake grows when it eats the food.
- **Collision Detection**: The game detects collisions with the snake's body and ends the game if a collision occurs.
- **Score Tracking**: The score is displayed and increases when the snake eats food.
- **Console-based Game**: The game runs in a Windows console with a simple text-based interface.

## Game Controls
The game uses the following keyboard inputs to control the snake:
- **W** or **w**: Move Up
- **A** or **a**: Move Left
- **S** or **s**: Move Down
- **D** or **d**: Move Right

## Code Explanation
### Classes
- **Point**: This structure represents a point on the board with `xCoord` and `yCoord` representing the x and y coordinates of the point.
- **Snake**: This class contains the snake's body as an array of `Point`s. It tracks the direction and movement of the snake, as well as checking for collisions and growing when food is eaten.
- **Board**: This class handles the game's main functionality, including spawning food, drawing the game state, updating the board, and handling user input. It also keeps track of the score and checks if the snake collides with itself or the walls.

### Functions
- `initScreen()`: Initializes the console screen's width and height.
- `hideCursor()`: Hides the cursor to provide a cleaner game experience.
- `gotoxy(x, y)`: Moves the console cursor to the specified x and y coordinates.
- `draw()`: Draws the game state, including the snake, food, and score.
- `update()`: Updates the game state, moves the snake, checks for collisions, and checks if the snake has eaten the food.
- `getInput()`: Handles user input to change the snake's direction.

## Compiling and Running the Game
To compile and run the Snake game, follow these steps:

1. Make sure you are using a C++ compiler that supports C++11 or later.
2. Save the code to a file named `snake.cpp`.
3. Open a terminal and navigate to the folder containing the `snake.cpp` file.
4. Compile the code using the following command:
   ```bash
   g++ -o snake snake.cpp
   ```
5. Run the compiled program:
   ```bash
   ./snake
   ```

## Screenshots
![Snake Game Screenshot](Screenshot%202025-02-09%20200253.png)

## Conclusion
The Snake game implemented in C++ is a fun and simple console-based game that demonstrates basic concepts such as collision detection, movement logic, and user input handling. It can be further extended to add features like levels, different difficulties, or enhanced graphics. This implementation provides a solid foundation for anyone looking to learn or enhance their understanding of game development in C++.

## License
This project is open-source and available under the MIT License.
