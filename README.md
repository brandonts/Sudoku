# Sudoku-Solver

This Repository is for me to develop a C++ program that solves sudoku puzzles.

Currently there is:
  (1) sudoku_puzzle.h provides the SudokuPuzzle class that holds the data structure and controls the data.
  (2) sudoku_solver.h provides the SudokuSolver function which contains the logic for solving a SudokuPuzzle.
  (3) sudoku_tester.cc is a test suite to provide unit testing.
  (4) sudoku_solver.cc is the front end that allows the user to enter a SudokuPuzzle and recieve a solution.

To do List:  
  add more comprehensive unit testing
  improve user interface: add input validation, show where user is in input, allow corrections
  complete sudoku_solver.h so it is not always using brute force to solve

Future possibilities:
  (1) gui for entering a puzzle to be solved
  (2) ability to save a puzzles
  (3) sudoku game with hints
