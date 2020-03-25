# Sudoku-Solver

This Repository is for me to develop a C++ program that solves sudoku puzzles.

Currently there is:
  (1) sudoku_puzzle.h provides the SudokuPuzzle class that holds the data, modifies the data, and provides functions that work with the SudokuPuzzle class.
    Logic:
      -Recursive guess and check grinder

      -OnlyPossible finds squares that are the only spot left for a certain value in a box,column, or row.

      -Elimination find squares that have only one value possible because other 8 have been eliminated

  (2) sudoku_solver.cc is the user interface.  It allows the user to enter a SudokuPuzzle and recieve a solution.

  (3) sudoku_solver.h holds the functions sudoku_solver.cc used primarily for displaying information.

  (4) sudoku_tester.cc is a test suite to provide unit testing.


To do List:  
  Check_() can not detect when the only spot for a number is blocked
  Save and Load puzzles
  Partial Solve in user interface



Future possibilities:
  (1) gui for entering a puzzle to be solved
  (2) ability to save puzzles
  (3) sudoku game with hints
