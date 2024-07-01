# Tic-tac-toe
Tic-tac-toe game 

# Tic-Tac-Toe Game with AI

This project implements a Tic-Tac-Toe game in C++ with multiple play modes, including an AI opponent using the Minimax algorithm.

## Features

- Multiple game modes:
  1. Human vs. Human
  2. Human vs. Computer (Minimax AI)
  3. Human vs. Computer (Random moves)
  4. Computer vs. Computer (Minimax AI)
- Interactive command-line interface
- Minimax algorithm for intelligent computer moves
- Flexible `Board` class for game state management
- Object-oriented design with `Player`, `HumanPlayer`, and `ComputerPlayer` classes

## How to Play

1. Compile the `minimax.cpp` file using a C++ compiler.
2. Run the executable.
3. Choose a game mode from the menu.
4. Follow the on-screen instructions to make moves.

## Classes

- `Board`: Manages the game board state and checks for wins/draws.
- `Player`: Abstract base class for all player types.
- `HumanPlayer`: Handles human player moves.
- `ComputerPlayer`: Implements AI moves (random or Minimax).
- `Game`: Orchestrates the game flow and player interactions.

## AI Implementation

The computer player can use two strategies:
1. Random moves
2. Minimax algorithm for optimal move selection

## Future Improvements

- Graphical user interface
- Difficulty levels for AI
- Network play functionality
- Game statistics tracking

## Contributing

Feel free to fork this project and submit pull requests with improvements or additional features.
