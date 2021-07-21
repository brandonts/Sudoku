# Sudoku-Solver

This Repository is for me to develop a C++ program that solves sudoku puzzles.

files in base program:
	sudoku_puzzle.h provides the SudokuPuzzle class that holds the data, modifies the data, and provides functions that work with the SudokuPuzzle class.

	sudoku_logic.h
		-Recursive guess and check grinder
		-OnlyPossible() finds squares that are the only spot left for a certain value in a box,column, or row.
		-Elimination() find squares that have only one value possible because other 8 have been eliminated
		-BlockLineElimination() checks each box to see if only one row or col is left because if it is you can block the possible values for that box
			from all squares in that row or col outside of the box in an elimination type sweep
		-BlockLineValueElimination() checks each box to see if any of its rows or cols have the only squares in that box that can hold any value.
		      when it finds such a row or col it it runs an elimination type sweep of the row or col with those values blocked

	sudoku_solver.cc is the user interface.  It allows the user to enter a SudokuPuzzle and recieve a solution.

	sudoku_tester.cc is a test suite to provide unit testing.

	sudoku_logic_stack.h is a refactor of Sudoku_logic.h using a stack for  guesses instead of recursion.

	ncurses_sudoku_solver.cc is an ncurses based user interface.
To do List:  
	Check_() can not detect when the only spot for a number is blocked
	Partial Solve in user interface



Future possibilities:
	(1) gui for entering a puzzle to be solved
	(3) sudoku game with hints
