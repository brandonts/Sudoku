# Sudoku-Solver

This Repository is for me to develop a C++ program that solves sudoku puzzles.

Currently there is:
  (1) sudoku_puzzle.h provides the SudokuPuzzle class that holds the data, modifies the data, and provides functions that work with the SudokuPuzzle class.

  (2) sudoku_solver.cc is the user interface.  It allows the user to enter a SudokuPuzzle and recieve a solution.

  (3) sudoku_solver.h holds the functions sudoku_solver.cc uses primarily for displaying information.

  (4) sudoku_tester.cc is a test suite to provide unit testing.


To do List:  
  complete sudoku_solver.h so it is not always using brute force to solve

Future possibilities:
  (1) gui for entering a puzzle to be solved
  (2) ability to save a puzzles
  (3) sudoku game with hints
