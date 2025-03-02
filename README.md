# Sudoku Game in C++

## Overview
This is a command-line Sudoku game implemented in C++ that allows players to generate and solve Sudoku puzzles of varying difficulty levels. It includes features such as a timer, undo functionality, and board validation.

## Features
- **Difficulty Levels:** Choose from Easy, Medium, or Hard.
- **Real-time Timer:** Tracks the duration of your gameplay.
- **Move Validation:** Ensures only valid Sudoku moves are placed.
- **Undo Functionality:** Allows you to revert the last move.
- **Automated Board Generation:** Generates a solvable Sudoku board.
- **Recursive Solver:** Ensures the board is solvable before starting the game.

## Installation
1. Clone this repository:
   ```sh
   git clone https://github.com/yourusername/sudoku-game.git
   ```
2. Navigate to the project directory:
   ```sh
   cd sudoku-game
   ```
3. Compile the code using g++:
   ```sh
   g++ -o sudoku sudoku.cpp -pthread
   ```
4. Run the executable:
   ```sh
   ./sudoku
   ```

## How to Play
1. Select a difficulty level (1 - Easy, 2 - Medium, 3 - Hard).
2. A Sudoku board will be generated and displayed.
3. Enter a number and its position (row and column) to place it on the board.
4. If you make a mistake, enter `-1` to undo your last move.
5. The game ends when the board is completely and correctly filled.

## Controls
- **Enter a number (1-9) and a position (row and column) to place it on the board.**
- **Enter `-1` to undo the last move.**

## Dependencies
- C++11 or later
- POSIX thread support (for timer functionality)

## Future Improvements
- GUI version using SDL or Qt
- Save and Load game functionality
- Online multiplayer mode

## License
This project is licensed under the MIT License.

## Author
Harmeet kaur

## Contributing
Feel free to fork the repository and submit pull requests for improvements!

